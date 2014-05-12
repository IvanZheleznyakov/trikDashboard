#pragma once
#include "dashboard_const.h"

#include <QObject>
#include <QTcpSocket>

class TcpCommunicator : public QObject
{
    Q_OBJECT
public:
    explicit TcpCommunicator(QObject *parent = 0);
    void setPort(int port);
    void setIP(QString ip);
    void connectToHost();
    int connectedState();

signals:
    void newConnection();
    void lostConnection();
    void recieveMessage(QString);

public slots:
    void send(QString);
    void setConnection();
    void abortConnection();

private slots:
    void read();

private:
    int         port;
    QString     ip;
    QTcpSocket* socket;
    quint16     blockSize;
};
