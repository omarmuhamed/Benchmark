#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H
#include <iostream>
#include <windows.h>
#include <Wbemidl.h>
#include <string>
#include <sstream>
#include <sysinfoapi.h>
#include <cpuid.h>
#include <QObject>
#include <QCryptographicHash>

class systeminfo : public QObject
{
    Q_OBJECT
public:
    systeminfo();
    Q_INVOKABLE QString getCPUInformation();
    Q_INVOKABLE QString getRAMInformation();
    Q_INVOKABLE QString getGPUInformation();
    Q_INVOKABLE QString getHardDiskInformation();
    Q_INVOKABLE QString calculateID();
    Q_INVOKABLE QString getRAMName();

private:
    HRESULT hres;
    IWbemServices* pSvc = NULL;
    IWbemLocator* pLoc = NULL;
    std::string ConvertBSTRToString(BSTR);
    BSTR ConvertStringToBSTR(const char*);
    HRESULT InitializeWMI(IWbemServices** , IWbemLocator** );
    void ReleaseWMI(IWbemServices*, IWbemLocator*);
};

#endif // SYSTEMINFO_H
