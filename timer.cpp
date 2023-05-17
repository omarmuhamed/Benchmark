#include "timer.h"

Timer::Timer()
{

}

void Timer::start(){
    QueryPerformanceCounter(&time);
}

void Timer::stop(double *duration){
    LARGE_INTEGER liDiff;
    LARGE_INTEGER liFreq;

    QueryPerformanceCounter(&liDiff);

    liDiff.QuadPart -= time.QuadPart;

    (void) QueryPerformanceFrequency(&liFreq);

    *duration = 1000.0 * (double) liDiff.QuadPart / (double) liFreq.QuadPart;
}
