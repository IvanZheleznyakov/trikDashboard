#pragma once

#include "icommunicator.h"

#include <QTcpSocket>

class TcpCommunicator : public ICommunicator
{
    Q_OBJECT

public:
    explicit TcpCommunicator();
    void setPort(int port);
    void setIP(QString ip);
    void connectToHost();
    bool isConnected();
    int connectedState();

signals:
    void newConnection();
    void lostConnection() ;
    void recieveMessage(QString);

public slots:
    void send(QString) ;
    void setConnection() ;
    void abortConnection() ;

protected slots:
    void read() ;

private:
    int         port;
    QString     ip;
    QTcpSocket* socket;
    quint16     blockSize;
};

