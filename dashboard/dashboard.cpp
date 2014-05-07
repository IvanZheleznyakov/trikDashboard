#include "dashboard.h"

Dashboard::Dashboard()
{
    connect(&tcpCommunicator, SIGNAL(recieveMessage(QString)), this, SLOT(parseMessage(QString)));

    connect(&panel, SIGNAL(setConnection(QString,int)), this, SLOT( connectToTRIK(QString,int)) );
    panel.resize(800, 600);
    panel.show();

    //connect(&panel, SIGNAL(readyCommand(QString)), this, SLOT(sendCommand(QString)));
}

void Dashboard::connectToTRIK(QString ip, int port)
{
    tcpCommunicator.setIP(ip.toLatin1());
    tcpCommunicator.setPort(port);
    tcpCommunicator.connectToHost();

    if (tcpCommunicator.connectedState()!= QTcpSocket::ConnectedState)
    {
        panel.setStatusBarText("Connected to TRIK");
        tcpCommunicator.send("Hi,Daemon, from Dashboard");
    } else
    {
        panel.setStatusBarText("Try to connect again");
    }

}

void Dashboard::parseMessage(QString message)
{
//    qDebug() << message;
    //panel.setLabelText(message);
}

void Dashboard::sendCommand(QString command)
{
    tcpCommunicator.send(command);
}

