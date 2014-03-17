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
    if (!canRead)
    {
        return;
    }
    QVector<int> temp;
    temp << qrand() << qrand() << qrand();
    value = temp;
}

void AccelObserver::update()
{
    if (!canRead)
    {
        return;
    }
    QVector<int> temp;
    temp << qrand() << qrand() << qrand();
    value = temp;
}

