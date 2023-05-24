#include "wrapper.h"
#include <QDebug>
Wrapper::Wrapper()
{
    bench = new Benchmark();
    bench->moveToThread(&th);
    th.start();
    QObject::connect(bench, SIGNAL(intSerRSig(int,double)), this, SLOT(intSerRSlot(int,double)), Qt::UniqueConnection);
    QObject::connect(bench, SIGNAL(intSerRWSig(int,double)), this, SLOT(intSerRWSlot(int,double)), Qt::UniqueConnection);
    QObject::connect(bench, SIGNAL(intRandRSig(int,double)), this, SLOT(intRandRSlot(int,double)), Qt::UniqueConnection);
    QObject::connect(bench, SIGNAL(intRandRWSig(int,double)), this, SLOT(intRandRWSlot(int,double)), Qt::UniqueConnection);
    QObject::connect(bench, SIGNAL(fltSerRSig(int,double)), this, SLOT(fltSerRSlot(int,double)), Qt::UniqueConnection);
    QObject::connect(bench, SIGNAL(fltSerRWSig(int,double)), this, SLOT(fltSerRWSlot(int,double)), Qt::UniqueConnection);
    QObject::connect(bench, SIGNAL(fltRandRSig(int,double)), this, SLOT(fltRandRSlot(int,double)), Qt::UniqueConnection);
    QObject::connect(bench, SIGNAL(fltRandRWSig(int,double)), this, SLOT(fltRandRWSlot(int,double)), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(startBench()), bench, SLOT(start()), Qt::UniqueConnection);
    QObject::connect(bench, SIGNAL(sendScore(int)), this, SLOT(scoreSlot(int)), Qt::UniqueConnection);

}

void Wrapper::scoreSlot(int score){
    emit scoreSig(score);
    isWorking = false;
}
void Wrapper::intSerRSlot(int size, double speed){
    emit intSerRSig(size, speed);
}

void Wrapper::intSerRWSlot(int size, double speed){
    emit intSerRWSig(size, speed);
}

void Wrapper::intRandRSlot(int size, double speed){
    emit intRandRSig(size, speed);
}

void Wrapper::intRandRWSlot(int size, double speed){
    emit intRandRWSig(size, speed);
}

void Wrapper::fltSerRSlot(int size, double speed){
    emit fltSerRSig(size, speed);
}

void Wrapper::fltSerRWSlot(int size, double speed){
    emit fltSerRWSig(size, speed);
}

void Wrapper::fltRandRSlot(int size, double speed){
    emit fltRandRSig(size, speed);
}

void Wrapper::fltRandRWSlot(int size, double speed){
    emit fltRandRWSig(size, speed);
}

void Wrapper::start(){
    if (!isWorking){
        isWorking = true;
        emit startBench();
    }

}
