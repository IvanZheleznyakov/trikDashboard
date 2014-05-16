#include "observer.h"
#include <QDebug>

Observer::Observer(QString devName, Brick *brick, Daemon* daemon)
{
    name = devName;
    canRead = false;
    brickbase = brick;
    daemon->attach(this);
}

void GyroObserver::update()
{
    if (!canRead)
    {
        return;
    }
    QVector<int> temp = brickbase->gyroscope()->read();
    value = temp;
}

void AccelObserver::update()
{
    if (!canRead)
    {
        return;
    }
    QVector<int> temp = brickbase->accelerometer()->read();
    value = temp;
}

void BatteryObserver::update()
{
    if (!canRead)
    {
        return;
    }
    QVector<float> temp;
    temp << brickbase->battery()->readVoltage();
    value = temp;
}
