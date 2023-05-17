#ifndef TIMER_H
#define TIMER_H
#include <windows.h>


class Timer
{
public:
    Timer();
    void start();
    void stop(double *);

private:
    LARGE_INTEGER time;
};

#endif // TIMER_H
