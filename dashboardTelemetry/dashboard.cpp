#include "dashboard.h"
#include <QThread>

Dashboard::Dashboard(ICommunicator *communicator)
{
    connect(&panel, &ControlPanel::setConnection, this, &Dashboard::connectToTRIK);

    facade = new Facade(communicator);

    panel.resize(PANEL_START_SIZE);
    panel.setMinimumSize(PANEL_MIN_SIZE);
    panel.show();
}

void Dashboard::connectToTRIK(QString ip, int port)
{
    panel.setStatusBarText(TelemetryConst::WAITING_RESPONSE_MESSAGE());
    QThread::msleep(WAITING_RESPONSE_TIME);
    if (facade->connectToTRIK(ip, port)) {
        panel.setStatusBarText(TelemetryConst::SEND_FROM_DAEMON_MESSAGE());
        emit panel.newConnection();
    } else {
        panel.setStatusBarText(TelemetryConst::NOCONNECTION_MESSAGE());
    }
}
