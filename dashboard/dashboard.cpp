#include "dashboard.h"

Dashboard::Dashboard()
{
    connect(&tcpCommunicator, SIGNAL(recieveMessage(QString)), this, SLOT(parseMessage(QString)));
    tcpCommunicator.setIP("192.168.1.37");
    tcpCommunicator.setPort(1221);
    tcpCommunicator.connectToHost();
    tcpCommunicator.send("Hi,Daemon, from Dashboard");

    panel.show();
    connect(&panel, SIGNAL(readyCommand(QString)), this, SLOT(sendCommand(QString)));
}

Dashboard::~Dashboard()
{

}

void Dashboard::parseMessage(QString message)
{
//    qDebug() << message;
    panel.setLabelText(message);
}

void Dashboard::sendCommand(QString command)
{
    tcpCommunicator.send(command);
}
