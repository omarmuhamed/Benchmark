#ifndef WRAPPER_H
#define WRAPPER_H
#include "benchmark.h"
#include <QThread>


class Wrapper : public QObject
{
    Q_OBJECT
public:
    Wrapper();
    Benchmark *bench;
    QThread th;
public slots:
    void intSerRSlot(int, double);
    void intSerRWSlot(int, double);
    void intRandRSlot(int, double);
    void intRandRWSlot(int, double);
    void fltSerRSlot(int, double);
    void fltSerRWSlot(int, double);
    void fltRandRSlot(int, double);
    void fltRandRWSlot(int, double);
    void start();
signals:
    void intSerRSig(int, double);
    void intSerRWSig(int, double);
    void intRandRSig(int, double);
    void intRandRWSig(int, double);
    void fltSerRSig(int, double);
    void fltSerRWSig(int, double);
    void fltRandRSig(int, double);
    void fltRandRWSig(int, double);
    void startBench();
};

#endif // WRAPPER_H