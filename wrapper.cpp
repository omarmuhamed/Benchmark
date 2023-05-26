#include "wrapper.h"
#include <QDebug>
#include <QEventLoop>
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

void Wrapper::sendPostRequest(QUrl& url, QJsonObject& jsonPayload)
{
    // Create a network access manager
    QNetworkAccessManager networkManager;

    // Create a JSON document from the payload
    QJsonDocument jsonDoc(jsonPayload);
    QByteArray jsonData = jsonDoc.toJson();

    // Create the request
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Send the POST request without waiting for a reply
    QNetworkReply* reply = networkManager.post(request, jsonData);
    reply->ignoreSslErrors();
    // Create an event loop to wait for the request to finish
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    // Wait for the request to finish
    loop.exec();

    // Check for errors
    if (reply->error() != QNetworkReply::NoError) {
        // Print the error message
        qCritical() << "POST request error:" << reply->errorString();
    } else {
        // Request succeeded, handle the response if needed
        QByteArray responseData = reply->readAll();
        qDebug() << responseData;
    }

    // Clean up
    reply->deleteLater();
}
void Wrapper::replyFinished(QNetworkReply* reply)
{
    QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        qDebug() << statusCodeV;
    if (statusCodeV.toInt()==200){
        //do something
    }
    else{
        // do something else
        }

    delete reply;
}

void Wrapper::scoreSlot(int score){
    emit scoreSig(score);
    isWorking = false;
    QJsonObject object
        {
            {"hash", _uid},
            {"device", _name},
            {"score", score}
        };
    QUrl url("https://ukdriving.omarmohamed.com/AddResult");
    sendPostRequest(url, object);
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

void Wrapper::setID(QString _id){
    _uid = _id;
}

void Wrapper::setName(QString name){
    _name = name;
}

QString Wrapper::getID(){
    return _uid;
}
