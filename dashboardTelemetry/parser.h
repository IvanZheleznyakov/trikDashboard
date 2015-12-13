#pragma once

#include <QObject>
#include "telemetry_const.h"

class Parser : public QObject
{
    Q_OBJECT

public:
    Parser();
    void parseMessage(QString message);
};

