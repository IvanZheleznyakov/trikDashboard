#pragma once
#include <QObject>
#include "tcpcommunicator.h"

class Daemon : public QObject
{
    Q_OBJECT
public:
    explicit Daemon(QObject *parent = 0);

signals:

public slots:

private slots:
    void sayHi();
    void parseMessage(QString message);

private:
    TcpCommunicator tcpCommunicator;
};

