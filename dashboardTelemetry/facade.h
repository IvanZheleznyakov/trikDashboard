#pragma once

#include "icommunicator.h"
#include "parser.h"

#include <QObject>

class Facade : QObject
{
    Q_OBJECT

public:
    Facade(ICommunicator *mCommunicator);
    bool connectToTRIK(QString ip, int port);

private:
    ICommunicator *mCommunicator;
    Parser *mParser;
};

