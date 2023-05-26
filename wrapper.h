#ifndef WRAPPER_H
#define WRAPPER_H
#include "benchmark.h"
#include <QThread>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>
class Wrapper : public QObject
{
    Q_OBJECT
public:
    Wrapper();
    QThread th;
    Benchmark *bench;
    void setID(QString);
    void setName(QString);
    Q_INVOKABLE QString getID();
private:
    bool isWorking = false;
    void sendPostRequest(QUrl& , QJsonObject&);
    QString _name;
    QString _uid;
public slots:
    void intSerRSlot(int, double);
    void intSerRWSlot(int, double);
    void intRandRSlot(int, double);
    void intRandRWSlot(int, double);
    void fltSerRSlot(int, double);
    void fltSerRWSlot(int, double);
    void fltRandRSlot(int, double);
    void fltRandRWSlot(int, double);
    void scoreSlot(int);
    void start();
    void replyFinished(QNetworkReply*);
signals:
    void intSerRSig(int, double);
    void intSerRWSig(int, double);
    void intRandRSig(int, double);
    void intRandRWSig(int, double);
    void fltSerRSig(int, double);
    void fltSerRWSig(int, double);
    void fltRandRSig(int, double);
    void fltRandRWSig(int, double);
    void scoreSig(int);
    void startBench();
};

#endif // WRAPPER_H
