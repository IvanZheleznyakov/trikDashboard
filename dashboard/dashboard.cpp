#include "dashboard.h"

Dashboard::Dashboard(QWidget *parent)
    : QWidget(parent)
{
    connect(&tcpCommunicator, SIGNAL(recieveMessage(QString)), this, SLOT(parseMessage(QString)));
    tcpCommunicator.setIP("192.168.1.37");
    tcpCommunicator.setPort(1221);
    tcpCommunicator.connectToHost();
    tcpCommunicator.send("Hi,");
    tcpCommunicator.send("Daemon");
    tcpCommunicator.send("from Dashboard");

}

Dashboard::~Dashboard()
{

}

void Dashboard::parseMessage(QString message)
{
    qDebug()<<message;
}
