#pragma once
#include "telemetry_const.h"

#include <QObject>
#include <QVector>
#include <QTimer>
#include <trikControl/brick.h>
#include "observer.h"
#include "tcpcommunicator.h"

using namespace trikControl;

class Observer;
class GyroObserver;
class AccelObserver;
class BatteryObserver;

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
    Brick brick;
    TcpCommunicator tcpCommunicator;
    QVector<Observer *> observers;
    GyroObserver *gyroObserver;
    AccelObserver *accelObserver;
    BatteryObserver* batteryObserver;

    QTimer timer;

    int updatePeriod;
};
