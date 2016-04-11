#pragma once
#include "telemetry_const.h"

#include <QObject>
#include "controlpanel.h"
#include "facade.h"
#include "icommunicator.h"

class Dashboard : public QObject
{
    Q_OBJECT

public:
    Dashboard(ICommunicator *communicator);

signals:

private slots:
    void connectToTRIK(QString ip, int port);

private:
    ControlPanel mPanel;
    Facade *mFacade;
};
