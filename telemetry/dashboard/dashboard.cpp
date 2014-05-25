#include "dashboard.h"
#include <QThread>

Dashboard::Dashboard():
    hi(false)
{
    connect(&tcpCommunicator, SIGNAL(recieveMessage(QString)), this, SLOT(parseMessage(QString)));
    connect(&panel, SIGNAL(setConnection(QString,int)), this, SLOT( connectToTRIK(QString,int)) );
    connect(&tcpCommunicator, SIGNAL(newConnection()), &panel, SIGNAL(newConnection()));
    connect(&tcpCommunicator, SIGNAL(lostConnection()), &panel, SIGNAL(lostConnection()));

    panel.resize(PANEL_START_SIZE);
    panel.setMinimumSize(PANEL_MIN_SIZE);
    panel.show();
}

void Dashboard::connectToTRIK(QString ip, int port)
{
    tcpCommunicator.setIP(ip.toLatin1());
    tcpCommunicator.setPort(port);
    tcpCommunicator.connectToHost();

    panel.setStatusBarText(WAITING_RESPONSE_MESSAGE);
    tcpCommunicator.send(SEND_MESSAGE);

    QThread::msleep(WAITING_RESPONSE_TIME);

    if (tcpCommunicator.connectedState() == QTcpSocket::ConnectedState)
    {
        foreach (Sensor* s, panel.sensors) {
            connect(s, SIGNAL(command(QString)), this, SLOT(sendCommand(QString)));
        }
    } else {
        panel.setStatusBarText(NOCONNECTION_MESSAGE);
    }
}

void Dashboard::parseMessage(QString message)
{
    if (!hi)
    {
        hi = true;
        panel.setStatusBarText(message);
        return;
    }
    /*
    qDebug() << "receive: " << message;
    panel.setStatusBarText(message);
    */
    QStringList devices = message.split(";", QString::SkipEmptyParts);
    foreach (QString device, devices)
    {
        QStringList info = device.split(":", QString::SkipEmptyParts);
        QVector<float> values;
        QStringList data = info.at(1).split("*", QString::SkipEmptyParts);
        foreach (QString val, data)
        {
            float x = val.toFloat();
            values << x;
        }
        QString const deviceName = info.at(0);

        if (deviceName == ACCELEROMETER_NAME && panel.accelerometer->active())
        {
            panel.accelerometer->widget()->updateData(values);
        } else
        if (deviceName == GYROSCOPE_NAME && panel.gyroscope->active())
        {
            panel.gyroscope->widget()->updateData(values);
        } else
        if (deviceName == POWER_MOTOR1_NAME && panel.powerMotor1->active())
        {
            panel.powerMotor1->widget()->updateData(values);
        }
        if (deviceName == BATTERY_NAME && panel.battery->active())
        {
            panel.battery->widget()->updateData(values);
        }
    }
}

void Dashboard::sendCommand(QString command)
{
    //qDebug() <<"send: " << command;
    tcpCommunicator.send(command);
}

