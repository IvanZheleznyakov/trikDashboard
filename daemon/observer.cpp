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
    //temp << qrand() << qrand() << qrand();
    value = temp;
}

void AccelObserver::update()
{
    if (!canRead)
    {
        return;
    }
    QVector<int> temp = brickbase->accelerometer()->read();
    //temp << qrand() << qrand() << qrand();
    value = temp;
}

