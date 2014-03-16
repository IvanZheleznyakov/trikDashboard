#include "observer.h"
#include <QDebug>

Observer::Observer(QString devName, Daemon* daemon)
{
    name = devName;
    canRead = false;
    daemon->attach(this);
}

void GyroObserver::update()
{
    qDebug() << "gyro update";
/*
    if (!canRead)
    {
        qDebug() << "gyro unsubscribed";
        return;
    }
    qDebug() << "GYRO UPDATE";
*/
}

void AccelObserver::update()
{
    qDebug() << "accel update";
/*
    if (!canRead)
    {
        qDebug() << "accel unsubscribed";
        return;
    }
    qDebug() << "ACCEL UPDATE";
*/
}

