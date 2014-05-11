#include "dashboard.h"

Dashboard::Dashboard()
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

    if (tcpCommunicator.connectedState()!= QTcpSocket::ConnectedState)
    {
        panel.setStatusBarText("Connected to TRIK");

        connect(panel.accelerometer,SIGNAL(command(QString)),this,SLOT(sendCommand(QString)));
        connect(panel.gyroscope,SIGNAL(command(QString)),this,SLOT(sendCommand(QString)));



        tcpCommunicator.send("Hi,Daemon, from Dashboard");
    } else
    {
        panel.setStatusBarText("No connection: Try to connect again");
    }
}

void Dashboard::parseMessage(QString message)
{
    panel.setStatusBarText(message);
}

void Dashboard::sendCommand(QString command)
{
    tcpCommunicator.send(command);
}

