#pragma once

#include <trikControl/brick.h>
#include <QObject>
#include <QTimer>

using namespace trikControl;

class RobotAlgorithm : public QObject
{
    Q_OBJECT
public:
    explicit RobotAlgorithm(Brick* brickbase, QObject *parent = 0);
    
public slots:
    void start();
    void stop();

private slots:
    void doAlgorithm();

private:
    Brick* brick;
    QTimer timer;
    int m1;
    int m2;
    int m3;
    int m4;
    int count;
};
