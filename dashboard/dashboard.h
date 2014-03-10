#pragma once

#include <QWidget>
#include "tcpcommunicator.h"

class Dashboard : public QWidget
{
    Q_OBJECT

public:
    Dashboard(QWidget *parent = 0);
    ~Dashboard();
private slots:
    void parseMessage(QString message);

private:
    TcpCommunicator tcpCommunicator;

};
