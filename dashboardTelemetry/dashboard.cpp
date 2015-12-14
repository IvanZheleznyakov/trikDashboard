#include "dashboard.h"
#include <QThread>

Dashboard::Dashboard(ICommunicator *communicator)
{
    connect(&mPanel, &ControlPanel::setConnection, this, &Dashboard::connectToTRIK);
    connect(&mPanel, &ControlPanel::subscribeWidgetToDataSource, mFacade, &Facade::subscribeWidgetToDataSource);
    connect(&mPanel, &ControlPanel::unscribeWidgetToDataSource, mFacade, &Facade::unscribeWidgetToDataSource);

    mFacade = new Facade(communicator);

    mPanel.resize(PANEL_START_SIZE);
    mPanel.setMinimumSize(PANEL_MIN_SIZE);
    mPanel.show();
}

void Dashboard::connectToTRIK(QString ip, int port)
{
    mPanel.setStatusBarText(TelemetryConst::WAITING_RESPONSE_MESSAGE());
    QThread::msleep(WAITING_RESPONSE_TIME);
    if (mFacade->connectToTRIK(ip, port)) {
        mPanel.setStatusBarText(TelemetryConst::SEND_FROM_DAEMON_MESSAGE());
        emit mPanel.newConnection();
    } else {
        mPanel.setStatusBarText(TelemetryConst::NOCONNECTION_MESSAGE());
    }
}
