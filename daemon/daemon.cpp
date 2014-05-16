#include "daemon.h"
#include <QDebug>
#include <QStringList>

Daemon::Daemon(QThread *guiThread, QString configPath) :
    brick(*guiThread, configPath)

{
    updatePeriod = 0;

    tcpCommunicator.setPort(START_PORT_INT);
    tcpCommunicator.listen();
    connect(&tcpCommunicator, SIGNAL(newConnection()), this, SLOT(startTelemetry()));
    connect(&tcpCommunicator, SIGNAL(recieveMessage(QString)), this, SLOT(parseMessage(QString)));
    connect(&tcpCommunicator, SIGNAL(lostConnection()), this, SLOT(closeTelemetry()));

    gyroObserver = new GyroObserver(GYROSCOPE_NAME, &brick, this);
    gyroObserver->setUpdateInterval(SENSORS3D_DATA_UPDATE_PERIOD);
    accelObserver = new AccelObserver(ACCELEROMETER_NAME, &brick, this);
    accelObserver->setUpdateInterval(SENSORS3D_DATA_UPDATE_PERIOD);
    batteryObserver = new BatteryObserver(BATTERY_NAME, &brick, this);
    batteryObserver->setUpdateInterval(BATTERY_DATA_UPDATE_PERIOD);

    for (int i = 0; i < observers.size(); i++)
        qDebug() << observers[i]->getName();

}

void Daemon::closeTelemetry()
{
    qDebug() << "TELEMETRY CLOSED";
    timer.stop();
    disconnect(&timer, SIGNAL(timeout()), this, SLOT(zipPackage()));
    for (int i = 0; i < observers.size(); i++)
        observers[i]->unsubscribe();
}

void Daemon::notify()
{
    for (int i = 0; i < observers.size(); i++)
        observers[i]->update();
}

void Daemon::attach(Observer *obs)
{
    observers.push_back(obs);
}

void Daemon::startTelemetry()
{
    tcpCommunicator.send(SEND_FROM_DAEMON_MESSAGE);

    timer.stop();
    connect(&timer, SIGNAL(timeout()), this, SLOT(zipPackage()));
    timer.start(updatePeriod);

}

void Daemon::zipPackage()
{
    QString package;

    for (int i = 0; i < observers.size(); i++)
    {
        if (observers[i]->subscribed() && observers[i]->freshData())
        {
            QVector<float> data = observers[i]->getValue();
            QString dataString;
            for (int j = 0; j < data.size() - 1; j++)
                dataString += QString::number(data[j]) + "*";
            dataString += QString::number(data[data.size() - 1]) + ";";
            QString obsMessage = observers[i]->getName() + ":" + dataString;
            package += obsMessage;
        }
    }
    if (package.size() > 0)
    {
        qDebug() << package ;
        tcpCommunicator.send(package);
    }

}

void Daemon::parseMessage(QString message)
{
    qDebug() << message;
    QStringList list = message.split(":", QString::SkipEmptyParts);

    if (list.at(0).trimmed() == "subscribe")
    {
        for (int i = 0; i < observers.size(); i++)
        {
            if (observers[i]->getName() == list.at(1).trimmed())
            {
                observers[i]->subscribe();
            }
        }
    } else
    if (list.at(0).trimmed() == "unsubscribe")
    {
        for (int i = 0; i < observers.size(); i++)
        {
            if (observers[i]->getName() == list.at(1).trimmed())
            {
                observers[i]->unsubscribe();
            }
        }
    }
}
