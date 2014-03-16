#pragma once

#include <QObject>
#include "tcpcommunicator.h"
#include "controlpanel.h"

class Dashboard : public QObject
{
    Q_OBJECT

public:
    Dashboard();
    ~Dashboard();
private slots:
    void parseMessage(QString message);
    void sendCommand(QString command);

private:
    TcpCommunicator tcpCommunicator;
    ControlPanel panel;
};
