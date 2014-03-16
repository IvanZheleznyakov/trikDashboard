#pragma once

#include <QObject>
#include <QVector>
#include <QTimer>
//#include <trikControl/brick.h>
#include "observer.h"
#include "tcpcommunicator.h"

QString const accelName = "accelerometer";
QString const gyroName = "gyroscope";

//using namespace trikControl;

class Observer;

class Daemon : public QObject
{
    Q_OBJECT
public:
    explicit Daemon(QThread *guiThread, QString configPath);
    void attach(Observer *obs);

signals:

public slots:

private slots:
    void notify();
    void zipPackage();
    void startTelemetry();
    void closeTelemetry();
    void parseMessage(QString message);

private:
//    Brick brick;
    TcpCommunicator tcpCommunicator;
    QVector<Observer *> observers;
    QTimer timer;
    int updatePeriod;
};
