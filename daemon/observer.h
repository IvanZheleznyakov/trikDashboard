#pragma once
#include "telemetry_const.h"

#include <QObject>
#include <trikControl/brick.h>
#include "daemon.h"

using namespace trikControl;

class Daemon;

class Observer : public QObject
{
    Q_OBJECT

public:
    explicit Observer(QString devName, Brick *brick, Daemon* daemon);
    virtual void update() = 0;

    QVector<int> const &getValue() const { return value; }
    QString getName() { return name; }
    void subscribe() { canRead = true; }
    void unsubscribe() { canRead = false; }
    bool subscribed() { return canRead; }

protected:
    QString name;
    QVector<int> value;
    bool canRead;
    Brick *brickbase;
};

class GyroObserver: public Observer
{
public:
    explicit GyroObserver(QString devName, Brick *brick, Daemon* daemon):
        Observer(devName, brick, daemon)
    {
        value << 0 << 0 << 0;
    }
    void update();
};

class AccelObserver: public Observer
{
public:
    explicit AccelObserver(QString devName, Brick *brick, Daemon* daemon):
        Observer(devName, brick, daemon)
    {
        value << 0 << 0 << 0;
    }
    void update();
};
