#include "dashboard.h"

Dashboard::Dashboard():
    hi(false)
{
    connect(&tcpCommunicator, SIGNAL(recieveMessage(QString)), this, SLOT(parseMessage(QString)));
    connect(&panel, SIGNAL(setConnection(QString,int)), this, SLOT( connectToTRIK(QString,int)) );
    connect(&tcpCommunicator, SIGNAL(newConnection()), &panel, SIGNAL(newConnection()));
    connect(&tcpCommunicator, SIGNAL(lostConnection()), &panel, SIGNAL(lostConnection()));

    panel.resize(800, 600);
    panel.show();
    panel.setMinimumSize(640, 480);

    //connect на сенсоры с данными с платы
}

void Dashboard::connectToTRIK(QString ip, int port)
{
    tcpCommunicator.setIP(ip.toLatin1());
    tcpCommunicator.setPort(port);
    tcpCommunicator.connectToHost();

    if (tcpCommunicator.connectedState() == QTcpSocket::ConnectedState)
    {
        panel.setStatusBarText("Connected to TRIK");

        connect(panel.accelerometer, SIGNAL(command(QString)), this, SLOT(sendCommand(QString)));
        connect(panel.gyroscope, SIGNAL(command(QString)), this, SLOT(sendCommand(QString)));


        tcpCommunicator.send("Hi,Daemon, from Dashboard");
    } else
    {
        panel.setStatusBarText("No connection: Try to connect again");
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
    qDebug() << "receive: " << message;
    panel.setStatusBarText(message);
    QStringList devices = message.split(";", QString::SkipEmptyParts);
    foreach (QString device, devices)
    {
        QStringList info = device.split(":", QString::SkipEmptyParts);
        qDebug() << info.at(0);
        qDebug() << info.at(1);

        QVector<double> values;
        QStringList data = info.at(1).split(",", QString::SkipEmptyParts);
        foreach (QString val, data)
        {
            int x = val.toDouble();
            values << x;
        }

        if (info.at(0) == "accelerometer" && panel.accelerometer->active())
        {
            qDebug() << values;
            panel.accelerometer->widget()->updateData(values);
        } else
        if (info.at(0) == "gyroscope" && panel.accelerometer->active())
        {
            qDebug() << values;
            panel.gyroscope->widget()->updateData(values);
        }
    }
}

void Dashboard::sendCommand(QString command)
{
    qDebug() <<"send: " << command;
    tcpCommunicator.send(command);
}

