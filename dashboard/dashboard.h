#pragma once
#include "../telemetry_const.h"

#include <QObject>
#include "tcpcommunicator.h"
#include "controlpanel.h"

class Dashboard : public QObject
{
    Q_OBJECT

public:
    Dashboard();

signals:

private slots:
    void connectToTRIK(QString ip, int port);
    void parseMessage(QString message);
    void sendCommand(QString command);

private:
    TcpCommunicator tcpCommunicator;
    ControlPanel panel;
    bool hi;
};
