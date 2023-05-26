#ifndef BENCHMARK_H
#define BENCHMARK_H
#include <timer.h>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <QObject>
#include <vector>


enum TestType{
    SERIAL_INTEGER_READ,
    SERIAL_INTEGER_READWRITE,
    RANDOM_INTEGER_READ,
    RANDOM_INTEGER_READWRITE,
    SERIAL_DOUBLE_READ,
    SERIAL_DOUBLE_READWRITE,
    RANDOM_DOUBLE_READ,
    RANDOM_DOUBLE_READWRITE
};

class Benchmark : public QObject
{
    Q_OBJECT

public:
    Benchmark();
    void warmup();

public slots:
    void start();

private:
    void fillDoubleArraySerial();
    void fillIntArraySerial();
    void fillIntArrayRandom();
    void fillDoubleArrayRandom();
    double double_result;
    int int_result;
    int *int_array;
    double *double_array;
    Timer timer;
    double msecs;
    int score = 0;
    int _max_iters = 10;
    std::vector<double> _intSerR;
    std::vector<double> _intSerRW;
    std::vector<double> _intRndR;
    std::vector<double> _intRndRW;
    std::vector<double> _fltSerR;
    std::vector<double> _fltSerRW;
    std::vector<double> _fltRndR;
    std::vector<double> _fltRndRW;
    std::vector<int> _sizes;
    double runTime = 100.0;
    void update_iterations();
    int _size = 1536;
    int _iters = 1;
    double _speed;
    double _bytes = 4.0;
    void IntRandRW();
    void IntSerR();
    void IntSerRW();
    void IntRandR();
    void DbSerR();
    void DbSerRW();
    void DbRandR();
    void DbRandRW();
    void AllocateInteger();
    void FreeInteger();
    void AllocateDouble();
    void FreeDouble();
    void calculateSpeed();
    void runTest(TestType);
    void calculateScore();

signals:
    void intSerRSig(int, double);
    void intSerRWSig(int, double);
    void intRandRSig(int, double);
    void intRandRWSig(int, double);
    void fltSerRSig(int, double);
    void fltSerRWSig(int, double);
    void fltRandRSig(int, double);
    void fltRandRWSig(int, double);
    void sendScore(int);


};

#endif // BENCHMARK_H
