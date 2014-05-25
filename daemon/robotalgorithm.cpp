#include "robotalgorithm.h"
#include <QTime>
#include "math.h"

float const pi = 3.14;

RobotAlgorithm::RobotAlgorithm(Brick* brickbase, QObject *parent) :
    QObject(parent)
{
    brick = brickbase;
    m1 = 0;
    m2 = 100;
    m3 = 50;
    m4 = 25;
    count = 0;
    connect(&timer, SIGNAL(timeout()), this, SLOT(doAlgorithm()));
}

void RobotAlgorithm::start()
{
    timer.start(5);
}

void RobotAlgorithm::stop()
{
    timer.stop();
}

void RobotAlgorithm::doAlgorithm()
{
    count++;
    if (m1 == 100)
        m1 = 0;
    else
        m1 = m1 + 2;
    if (m2 == 0)
        m2 = 100;
    else m2 = m2 - 2;
    QTime time = QTime::currentTime();
    m3 = 50 - 20*sin(time.msec()*pi/500);
    m4 = (5*m1+7*m2+13*m3) % 101;

    brick->motor("M1")->setPower(m1);
    brick->motor("JM1")->setPower(m2);
    brick->motor("JM2")->setPower(m3);
    brick->motor("JM3")->setPower(m4);
}
