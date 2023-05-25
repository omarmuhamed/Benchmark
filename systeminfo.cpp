#include "systeminfo.h"
#include <QDebug>
systeminfo::systeminfo()
{
    hres = InitializeWMI(&pSvc, &pLoc);
}

QString systeminfo::getCPUInformation(){
    std::string cpuInfo;

    // Get processor name
    int CPUInfo[4] = { -1 };
    char CPUBrandString[0x40];
    __cpuid(0x80000000, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
    unsigned int nExIds = CPUInfo[0];
    for (unsigned int i = 0x80000000; i <= nExIds; ++i)
    {
        __cpuid(i, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
        if (i == 0x80000002)
            memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
        else if (i == 0x80000003)
            memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
        else if (i == 0x80000004)
            memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
    }
    cpuInfo += "CPU: ";
    cpuInfo += CPUBrandString;
    cpuInfo += "\n";

    // Get number of cores
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    cpuInfo += "Number of Cores: ";
    cpuInfo += std::to_string(sysInfo.dwNumberOfProcessors);
    cpuInfo += "\nArchitecture: ";
    switch (sysInfo.wProcessorArchitecture)
    {
    case PROCESSOR_ARCHITECTURE_INTEL:
        cpuInfo += "x86 (32-bit)";
        break;
    case PROCESSOR_ARCHITECTURE_AMD64:
        cpuInfo += "x64 (64-bit)";
        break;
    case PROCESSOR_ARCHITECTURE_ARM:
        cpuInfo += "ARM";
        break;
    case 12:
        cpuInfo += "ARM64";
        break;
    default:
        cpuInfo += "Unknown";
        break;
    }
    cpuInfo += "\n";

    return QString::fromStdString(cpuInfo);
}

// Function to initialize WMI
HRESULT systeminfo::InitializeWMI(IWbemServices** pSvc, IWbemLocator** pLoc) {
    HRESULT hres;

    // Initialize COM
    hres = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hres)) {
        return hres;
    }

    // Initialize security
    hres = CoInitializeSecurity(
        NULL,
        -1,
        NULL,
        NULL,
        RPC_C_AUTHN_LEVEL_DEFAULT,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL,
        EOAC_NONE,
        NULL
        );
    if (FAILED(hres)) {
        CoUninitialize();
        return hres;
    }

    // Obtain the initial locator
    hres = CoCreateInstance(
        CLSID_WbemLocator,
        0,
        CLSCTX_INPROC_SERVER,
        IID_IWbemLocator,
        reinterpret_cast<LPVOID*>(pLoc)
        );
    if (FAILED(hres)) {
        CoUninitialize();
        return hres;
    }

    // Connect to WMI
    hres = (*pLoc)->ConnectServer(
        ConvertStringToBSTR("ROOT\\CIMV2"),
        NULL,
        NULL,
        0,
        NULL,
        0,
        0,
        pSvc
        );
    if (FAILED(hres)) {
        (*pLoc)->Release();
        CoUninitialize();
        return hres;
    }

    // Set security levels
    hres = CoSetProxyBlanket(
        *pSvc,
        RPC_C_AUTHN_WINNT,
        RPC_C_AUTHZ_NONE,
        NULL,
        RPC_C_AUTHN_LEVEL_CALL,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL,
        EOAC_NONE
        );
    if (FAILED(hres)) {
        (*pSvc)->Release();
        (*pLoc)->Release();
        CoUninitialize();
        return hres;
    }

    return S_OK;
}

// Function to release WMI resources
void systeminfo::ReleaseWMI(IWbemServices* pSvc, IWbemLocator* pLoc) {
    pSvc->Release();
    pLoc->Release();
    CoUninitialize();
}

// Function to get RAM model and details
QString systeminfo::getRAMInformation() {
    std::string ramDetails;



    // Query for RAM details
    IEnumWbemClassObject* pEnumerator = NULL;
    hres = pSvc->ExecQuery(
        ConvertStringToBSTR("WQL"),
        ConvertStringToBSTR("SELECT * FROM Win32_PhysicalMemory"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &pEnumerator
        );
    if (FAILED(hres)) {
        ramDetails = "Failed to query for RAM details.";
        ReleaseWMI(pSvc, pLoc);
        return QString::fromStdString(ramDetails);
    }

    // Retrieve RAM details
    IWbemClassObject* pRAMObj = NULL;
    ULONG uReturn = 0;
    while (pEnumerator) {
        hres = pEnumerator->Next(WBEM_INFINITE, 1, &pRAMObj, &uReturn);
        if (uReturn == 0) {
            break;
        }

        VARIANT vtProp;
        hres = pRAMObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);
        if (SUCCEEDED(hres)) {
            ramDetails += "RAM Manufacturer: " + std::string(vtProp.vt == VT_NULL ? "Unknown" : ConvertBSTRToString(vtProp.bstrVal)) + "\n";
            VariantClear(&vtProp);
        }

        hres = pRAMObj->Get(L"PartNumber", 0, &vtProp, 0, 0);
        if (SUCCEEDED(hres)) {
            ramDetails += "RAM Part Number: " + std::string(vtProp.vt == VT_NULL ? "Unknown" : ConvertBSTRToString(vtProp.bstrVal)) + "\n";
            VariantClear(&vtProp);
        }
        //aVARIANT vtProp;
        hres = pRAMObj->Get(L"Capacity", 0, &vtProp, 0, 0);
        if (SUCCEEDED(hres)) {
            uint64_t ramCapacity;
            std::istringstream iss(ConvertBSTRToString(vtProp.bstrVal));
            iss >> ramCapacity;
            // Convert and format the RAM capacity to a string
            char buffer[32];
            snprintf(buffer, sizeof(buffer), "Capacity: %llu GB", ramCapacity / (1024 * 1024 * 1024));
            ramDetails += buffer;
            ramDetails += "\n";
            VariantClear(&vtProp);
        }
        hres = pRAMObj->Get(L"Speed", 0, &vtProp, 0, 0);
        if (SUCCEEDED(hres)) {
            ramDetails += "RAM Speed: " + std::string(vtProp.vt == VT_NULL ? "Unknown" : std::to_string(vtProp.intVal))+ " MHz\n";
            VariantClear(&vtProp);
        }

        ramDetails += "\n";
        pRAMObj->Release();
    }

    pEnumerator->Release();
    //ReleaseWMI(pSvc, pLoc);

    return QString::fromStdString(ramDetails);
}

QString systeminfo::getGPUInformation(){
    QString gpuInfo;
    IEnumWbemClassObject *pEnumerator = NULL;
    hres = pSvc->ExecQuery(
        ConvertStringToBSTR("WQL"),
        ConvertStringToBSTR("SELECT * FROM Win32_VideoController"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &pEnumerator);
    if (FAILED(hres))
    {
        // Handle query execution failure
        pSvc->Release();
        pLoc->Release();
        return gpuInfo;
    }

    // Retrieve and display the GPU information
    IWbemClassObject *pclsObj = NULL;
    ULONG uReturn = 0;
    while (pEnumerator)
    {
        hres = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
        if (uReturn == 0)
            break;

        VARIANT vtProp;
        hres = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
        if (SUCCEEDED(hres))
        {
            std::wstring gpuName = vtProp.bstrVal;
            gpuInfo += "GPU Name: ";
            gpuInfo += QString::fromStdWString(gpuName);
            gpuInfo += "\n";
            VariantClear(&vtProp);
        }

        hres = pclsObj->Get(L"AdapterRAM", 0, &vtProp, 0, 0);
        if (SUCCEEDED(hres))
        {
            unsigned long long ramSize = vtProp.uintVal;
            gpuInfo += "GPU RAM Size: ";
            gpuInfo += QString::number(ramSize / (1024 * 1024));
            gpuInfo += " MB\n";
            VariantClear(&vtProp);
        }

        pclsObj->Release();
        gpuInfo += '\n';
    }

    // Cleanup
    pEnumerator->Release();
    return gpuInfo;
}
QString systeminfo::getHardDiskInformation()
{
    QString info;

    IEnumWbemClassObject* pEnumerator = nullptr;
    hres = pSvc->ExecQuery(
        ConvertStringToBSTR("WQL"),
        ConvertStringToBSTR("SELECT * FROM Win32_DiskDrive"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        nullptr,
        &pEnumerator);
    if (FAILED(hres))
    {
        // Handle query execution failure
        pSvc->Release();
        pLoc->Release();
        return info;
    }

    // Retrieve and display the hard disk information
    IWbemClassObject* pclsObj = nullptr;
    ULONG uReturn = 0;
    while (pEnumerator)
    {
        hres = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
        if (uReturn == 0)
            break;

        VARIANT vtProp;
        hres = pclsObj->Get(L"Model", 0, &vtProp, 0, 0);
        if (SUCCEEDED(hres))
        {
            info += "Model: " + QString::fromWCharArray(vtProp.bstrVal) + "\n";
            VariantClear(&vtProp);
        }

        hres = pclsObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);
        if (SUCCEEDED(hres))
        {
            info += "Manufacturer: " + QString::fromWCharArray(vtProp.bstrVal) + "\n";
            VariantClear(&vtProp);
        }

        hres = pclsObj->Get(L"Size", 0, &vtProp, 0, 0);
        if (SUCCEEDED(hres))
        {
            unsigned long long size;
            std::istringstream iss(ConvertBSTRToString(vtProp.bstrVal));
            iss >> size;
            info += "Size: " + QString::number(size / (1024 * 1024 * 1024)) + " GB\n";
            VariantClear(&vtProp);
        }

        pclsObj->Release();
    }

    // Cleanup
    pEnumerator->Release();
    return info;
}

QString systeminfo::calculateID(){
    std::string ramDetails;



    // Query for RAM details
    IEnumWbemClassObject* pEnumerator = NULL;
    hres = pSvc->ExecQuery(
        ConvertStringToBSTR("WQL"),
        ConvertStringToBSTR("SELECT * FROM Win32_PhysicalMemory"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &pEnumerator
        );
    if (FAILED(hres)) {
        ramDetails = "Failed to query for RAM details.";
        ReleaseWMI(pSvc, pLoc);
        return QString::fromStdString(ramDetails);
    }

    // Retrieve RAM details
    IWbemClassObject* pRAMObj = NULL;
    ULONG uReturn = 0;
    while (pEnumerator) {
        hres = pEnumerator->Next(WBEM_INFINITE, 1, &pRAMObj, &uReturn);
        if (uReturn == 0) {
            break;
        }

        VARIANT vtProp;

        hres = pRAMObj->Get(L"PartNumber", 0, &vtProp, 0, 0);
        if (SUCCEEDED(hres)) {
            ramDetails += std::string(vtProp.vt == VT_NULL ? "Unknown" : ConvertBSTRToString(vtProp.bstrVal));
            VariantClear(&vtProp);
        }
        hres = pRAMObj->Get(L"SerialNumber", 0, &vtProp, 0, 0);
        if (SUCCEEDED(hres)) {
            ramDetails += std::string(vtProp.vt == VT_NULL ? "Unknown" : ConvertBSTRToString(vtProp.bstrVal));
            VariantClear(&vtProp);
        }
        pRAMObj->Release();
    }

    pEnumerator->Release();
    auto mystr = QString::fromStdString(ramDetails).simplified().remove(' ');
    auto hash = QCryptographicHash::hash(mystr.toUtf8(), QCryptographicHash::Sha256);
    return QString(hash.toHex());
}

QString systeminfo::getRAMName(){
    std::string ramDetails;



    // Query for RAM details
    IEnumWbemClassObject* pEnumerator = NULL;
    hres = pSvc->ExecQuery(
        ConvertStringToBSTR("WQL"),
        ConvertStringToBSTR("SELECT * FROM Win32_PhysicalMemory"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &pEnumerator
        );
    if (FAILED(hres)) {
        ramDetails = "Failed to query for RAM details.";
        ReleaseWMI(pSvc, pLoc);
        return QString::fromStdString(ramDetails);
    }

    // Retrieve RAM details
    IWbemClassObject* pRAMObj = NULL;
    ULONG uReturn = 0;
    while (pEnumerator) {
        hres = pEnumerator->Next(WBEM_INFINITE, 1, &pRAMObj, &uReturn);
        if (uReturn == 0) {
            break;
        }

        VARIANT vtProp;
        hres = pRAMObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);
        if (SUCCEEDED(hres)) {
            ramDetails += std::string(vtProp.vt == VT_NULL ? "Unknown" : ConvertBSTRToString(vtProp.bstrVal)) + " ";
            VariantClear(&vtProp);
        }

        hres = pRAMObj->Get(L"PartNumber", 0, &vtProp, 0, 0);
        if (SUCCEEDED(hres)) {
            ramDetails += std::string(vtProp.vt == VT_NULL ? "Unknown" : ConvertBSTRToString(vtProp.bstrVal)) + " ";
            VariantClear(&vtProp);
        }
        //aVARIANT vtProp;
        hres = pRAMObj->Get(L"Capacity", 0, &vtProp, 0, 0);
        if (SUCCEEDED(hres)) {
            uint64_t ramCapacity;
            std::istringstream iss(ConvertBSTRToString(vtProp.bstrVal));
            iss >> ramCapacity;
            // Convert and format the RAM capacity to a string
            char buffer[32];
            snprintf(buffer, sizeof(buffer), "%llu GB", ramCapacity / (1024 * 1024 * 1024));
            ramDetails += buffer;
            ramDetails += " ";
            VariantClear(&vtProp);
        }
        hres = pRAMObj->Get(L"Speed", 0, &vtProp, 0, 0);
        if (SUCCEEDED(hres)) {
            ramDetails += std::string(vtProp.vt == VT_NULL ? "Unknown" : std::to_string(vtProp.intVal)) + " MHz + ";
            VariantClear(&vtProp);
        }

        pRAMObj->Release();
    }

    pEnumerator->Release();
    //ReleaseWMI(pSvc, pLoc);

    return QString::fromStdString(ramDetails);
}
std::string systeminfo::ConvertBSTRToString(BSTR bstr)
{
    std::wstring ws(bstr);
    std::string str(ws.begin(), ws.end());
    return str;
}
BSTR systeminfo::ConvertStringToBSTR(const char* str)
{
    int length = MultiByteToWideChar(CP_ACP, 0, str, -1, nullptr, 0);
    BSTR bstr = SysAllocStringLen(nullptr, length);
    MultiByteToWideChar(CP_ACP, 0, str, -1, bstr, length);
    return bstr;
}

