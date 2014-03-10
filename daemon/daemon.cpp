#include "daemon.h"

Daemon::Daemon(QObject *parent) :
    QObject(parent)
{
    tcpCommunicator.setPort(1221);
    tcpCommunicator.listen();
    connect(&tcpCommunicator, SIGNAL(newConnection()), this, SLOT(sayHi()));
    connect(&tcpCommunicator, SIGNAL(recieveMessage(QString)), this, SLOT(parseMessage(QString)));
}

void Daemon::sayHi()
{
    tcpCommunicator.send("Hi,");
    tcpCommunicator.send("Dashboard");
    tcpCommunicator.send("from Daemon");
}

void Daemon::parseMessage(QString message)
{
    qDebug()<<message;
}
