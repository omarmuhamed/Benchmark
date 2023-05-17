#include "benchmark.h"
#include <QDebug>


Benchmark::Benchmark()
{
    timer = Timer();
}

void Benchmark::start(){
    for (int i = 0; i < 15; i++){
        _bytes = 4;
        AllocateInteger();
        fillIntArraySerial();
        runTest(SERIAL_INTEGER_READ);
        calculateSpeed();
        emit intSerRSig(_size / 256, _speed);
        fillIntArraySerial();
        runTest(SERIAL_INTEGER_READWRITE);
        calculateSpeed();
        emit intSerRWSig(_size / 256, _speed);
        fillIntArrayRandom();
        runTest(RANDOM_INTEGER_READ);
        calculateSpeed();
        emit intRandRSig(_size / 256, _speed);
        fillIntArrayRandom();
        runTest(RANDOM_INTEGER_READWRITE);
        calculateSpeed();
        emit intRandRWSig(_size / 256, _speed);
        FreeInteger();
        _size /= 3;
        _bytes = 12;
        AllocateInteger();
        AllocateDouble();
        fillDoubleArraySerial();
        runTest(SERIAL_DOUBLE_READ);
        calculateSpeed();
        emit fltSerRSig((_size * 3) / 256, _speed);
        fillDoubleArraySerial();
        runTest(SERIAL_DOUBLE_READWRITE);
        calculateSpeed();
        emit fltSerRWSig((_size * 3) / 256, _speed);
        fillDoubleArrayRandom();
        runTest(RANDOM_DOUBLE_READ);
        calculateSpeed();
        emit fltRandRSig((_size * 3) / 256, _speed);
        fillDoubleArrayRandom();
        runTest(RANDOM_DOUBLE_READWRITE);
        calculateSpeed();
        emit fltRandRWSig((_size * 3) / 256, _speed);
        _size *= 6;
        FreeDouble();
        FreeInteger();
    }
    _size = 1536;
    _speed = 0.0;
    _bytes = 4.0;
    _iters = 1;
}

void Benchmark::warmup(){
    const int SIZE = 1000000;  // Adjust the size based on your requirements

    // Allocate memory for an array of integers
    int* intArray = new int[SIZE];

    // Generate random values for the array
    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < SIZE; ++i) {
        intArray[i] = rand();
    }

    // Perform some dummy operations on the array
    for (int i = 0; i < SIZE; ++i) {
        intArray[i] += 1;
        intArray[i] *= 2;
    }

    // Clean up allocated memory
    delete[] intArray;
}

void Benchmark::AllocateInteger(){
    int_array = (int *) HeapAlloc(GetProcessHeap(), GPTR, _size * 4 + 8);
}

void Benchmark::FreeInteger(){
    HeapFree(GetProcessHeap(), GPTR, int_array);
}

void Benchmark::AllocateDouble(){
    double_array = (double *) HeapAlloc(GetProcessHeap(), GPTR, _size * 8 + 8);
}

void Benchmark::FreeDouble(){
    HeapFree(GetProcessHeap(), GPTR, double_array);
}

void Benchmark::IntSerR() {
    int i, j;
    timer.start();
    for (j = 0; j < _iters; j++) {
        int_result = 0;
        for (i = 0; i < _size; i = i + 32) {
            int_result = int_result & int_array[int_array[i + 0]] | int_array[int_array[i + 2]]
                                                            & int_array[int_array[i + 4]] | int_array[int_array[i + 6]]
                                                                                            & int_array[int_array[i +
                                                                                                                  8]] |
                     int_array[int_array[i + 10]]
                     & int_array[int_array[i + 12]] | int_array[int_array[i + 14]]
                                                      & int_array[int_array[i + 16]] | int_array[int_array[i + 18]]
                                                                                       & int_array[int_array[i + 20]] |
                     int_array[int_array[i + 22]]
                     & int_array[int_array[i + 24]] | int_array[int_array[i + 26]]
                                                      & int_array[int_array[i + 28]] | int_array[int_array[i + 30]];
        }
    }
    timer.stop(&msecs);
}

void Benchmark::IntSerRW() {
    int i, j;
    timer.start();
    for (j = 0; j < _iters; j++) {
        for (i = 0; i < _size; i = i + 32) {
            int_array[int_array[i + 2]] = int_array[int_array[i + 0]];
            int_array[int_array[i + 6]] = int_array[int_array[i + 4]];
            int_array[int_array[i + 10]] = int_array[int_array[i + 8]];
            int_array[int_array[i + 14]] = int_array[int_array[i + 12]];
            int_array[int_array[i + 18]] = int_array[int_array[i + 16]];
            int_array[int_array[i + 22]] = int_array[int_array[i + 20]];
            int_array[int_array[i + 26]] = int_array[int_array[i + 24]];
            int_array[int_array[i + 30]] = int_array[int_array[i + 28]];
        }
    }
    timer.stop(&msecs);
}

void Benchmark::IntRandRW() {
    int i, j;
    timer.start();
    for (j = 0; j < _iters; j++) {
        for (i = 0; i < _size; i = i + 32) {
            int_array[int_array[i + 28]] = int_array[int_array[i + 30]];
            int_array[int_array[i + 24]] = int_array[int_array[i + 26]];
            int_array[int_array[i + 20]] = int_array[int_array[i + 22]];
            int_array[int_array[i + 16]] = int_array[int_array[i + 18]];
            int_array[int_array[i + 12]] = int_array[int_array[i + 14]];
            int_array[int_array[i + 8]] = int_array[int_array[i + 10]];
            int_array[int_array[i + 4]] = int_array[int_array[i + 6]];
            int_array[int_array[i + 0]] = int_array[int_array[i + 2]];
        }
    }
    timer.stop(&msecs);

}

void Benchmark::IntRandR() {
    int i, j;
    timer.start();
    for (j = 0; j < _iters; j++) {
        int_result = 0;
        for (i = 0; i < _size; i = i + 32) {
            int_result = int_result & int_array[int_array[i + 30]] | int_array[int_array[i + 28]]
                                                             & int_array[int_array[i + 26]] |
                     int_array[int_array[i + 24]]
                     & int_array[int_array[i + 22]] | int_array[int_array[i + 20]]
                                                      & int_array[int_array[i + 18]] | int_array[int_array[i + 16]]
                                                                                       & int_array[int_array[i + 14]] |
                     int_array[int_array[i + 12]]
                     & int_array[int_array[i + 10]] | int_array[int_array[i + 8]]
                                                      & int_array[int_array[i + 6]] | int_array[int_array[i + 4]]
                                                                                      & int_array[int_array[i + 2]] |
                     int_array[int_array[i + 0]];
        }
    }
    timer.stop(&msecs);

}

void Benchmark::DbSerR(){
    int i, j;

        timer.start();
        for (j=0; j<_iters; j++)
        {
            double_result = 0.0;
            for (i=0; i<_size; i=i+16)
            {
                double_result = double_result + double_array[int_array[i+ 0]] * double_array[int_array[i+ 1]]
                            - double_array[int_array[i+ 2]] * double_array[int_array[i+ 3]]
                            + double_array[int_array[i+ 4]] * double_array[int_array[i+ 5]]
                            - double_array[int_array[i+ 6]] * double_array[int_array[i+ 7]]
                            + double_array[int_array[i+ 8]] * double_array[int_array[i+ 9]]
                            - double_array[int_array[i+10]] * double_array[int_array[i+11]]
                            + double_array[int_array[i+12]] * double_array[int_array[i+13]]
                            - double_array[int_array[i+14]] * double_array[int_array[i+15]];
            }
        }
        timer.stop(&msecs);
}

void  Benchmark::DbSerRW()
{
        int i, j;
        timer.start();

        for (j=0; j<_iters; j++)
        {
            for (i=0; i<_size; i=i+16)
            {
                double_array[int_array[i+ 1]] = double_array[int_array[i+ 0]];
                double_array[int_array[i+ 3]] = double_array[int_array[i+ 2]];
                double_array[int_array[i+ 5]] = double_array[int_array[i+ 4]];
                double_array[int_array[i+ 7]] = double_array[int_array[i+ 6]];
                double_array[int_array[i+ 9]] = double_array[int_array[i+ 8]];
                double_array[int_array[i+11]] = double_array[int_array[i+10]];
                double_array[int_array[i+13]] = double_array[int_array[i+12]];
                double_array[int_array[i+15]] = double_array[int_array[i+14]];
            }
        }
        timer.stop(&msecs);
}


void  Benchmark::DbRandR()
{
        int i, j;
        timer.start();

        for (j=0; j<_iters; j++)
        {
            double_result = 0.0;
            for (i=0; i<_size; i=i+16)
            {
                double_result = double_result + double_array[int_array[i+15]] * double_array[int_array[i+14]]
                       - double_array[int_array[i+13]] * double_array[int_array[i+12]]
                       + double_array[int_array[i+11]] * double_array[int_array[i+10]]
                       - double_array[int_array[i+ 9]] * double_array[int_array[i+ 8]]
                       + double_array[int_array[i+ 7]] * double_array[int_array[i+ 6]]
                       - double_array[int_array[i+ 5]] * double_array[int_array[i+ 4]]
                       + double_array[int_array[i+ 3]] * double_array[int_array[i+ 2]]
                       - double_array[int_array[i+ 1]] * double_array[int_array[i+ 0]];
            }
        }
        timer.stop(&msecs);

}

void Benchmark::DbRandRW()
{
        int i, j;
        timer.start();

        for (j=0; j<_iters; j++)
        {
            for (i=0; i<_size; i=i+16)
            {
                double_array[int_array[i+14]] = double_array[int_array[i+15]];
                double_array[int_array[i+12]] = double_array[int_array[i+13]];
                double_array[int_array[i+10]] = double_array[int_array[i+11]];
                double_array[int_array[i+ 8]] = double_array[int_array[i+ 9]];
                double_array[int_array[i+ 6]] = double_array[int_array[i+ 7]];
                double_array[int_array[i+ 4]] = double_array[int_array[i+ 5]];
                double_array[int_array[i+ 2]] = double_array[int_array[i+ 3]];
                double_array[int_array[i+ 0]] = double_array[int_array[i+ 1]];
            }
        }
        timer.stop(&msecs);
}

void Benchmark::fillIntArraySerial(){
    for (int i=0;i < _size+1; i++){
        int_array[i] = i+1;
    }
}

void Benchmark::fillIntArrayRandom(){
    srand(123);
    for (int i = 0; i<_size+1; i++) {
        int_array[i] = (int)((double)_size * ((double)(rand() * 32768 + rand()) / 32768 / 32768));
    }
}

void Benchmark::fillDoubleArraySerial(){
    for (int i = 0; i < _size+1; i++) {
        double_array[i] = 1.0;
        int_array[i] = i+1;
    }
}

void Benchmark::fillDoubleArrayRandom(){
    srand(123);
    for (int i = 0; i < _size+1; i++) {
        int_array[i] = (int)((double)_size * ((double)(rand() * 32768 + rand()) / 32768 / 32768));
        double_array[i] = 1.0;
    }
}

void Benchmark::update_iterations() {
    if (msecs < runTime) {
        if (msecs < runTime / 8.0) {
            _iters = _iters * 10;
        } else {
            _iters = (int) (runTime * 1.25 / msecs * (double) _iters + 1);
        }
    }
}

void Benchmark::calculateSpeed(){
    _speed = (double) _size * (double) _iters * _bytes / (1024.0 * 1024.0 * 1024.0) / (msecs / 1000.0);
}

void Benchmark::runTest(TestType test){
    _iters = 1;
    do {
        switch (test) {
        case SERIAL_INTEGER_READ:
            IntSerR();
            break;
        case SERIAL_INTEGER_READWRITE:
            IntSerRW();
            break;
        case RANDOM_INTEGER_READ:
            IntRandR();
            break;
        case RANDOM_INTEGER_READWRITE:
            IntRandRW();
            break;
        case SERIAL_DOUBLE_READ:
            DbSerR();
            break;
        case SERIAL_DOUBLE_READWRITE:
            DbSerRW();
            break;
        case RANDOM_DOUBLE_READ:
            DbRandR();
            break;
        case RANDOM_DOUBLE_READWRITE:
            DbRandRW();
            break;
        default:
            break;
        }
        update_iterations();
    } while (msecs < runTime);
}
