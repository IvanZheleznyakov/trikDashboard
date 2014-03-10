#pragma once
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

signals:
    void recieveMessage(QString);

public slots:
    void send(QString);

private slots:
    void read();

private:
    int         port;
    QString     ip;
    QTcpSocket* socket;
    quint16     blockSize;
};
