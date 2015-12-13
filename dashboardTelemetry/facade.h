#pragma once

#include "icommunicator.h"

#include <QObject>

class Facade : QObject
{
    Q_OBJECT

public:
    Facade(ICommunicator *communicator);
    bool connectToTRIK(QString ip, int port);

private:
    ICommunicator *communicator;
};
