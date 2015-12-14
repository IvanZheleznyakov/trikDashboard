#pragma once

#include "icommunicator.h"
#include "parser.h"

#include <QObject>

class Facade : public QObject
{
    Q_OBJECT

public:
    Facade(ICommunicator *mCommunicator);
    bool connectToTRIK(QString ip, int port);

signals:
    void subscribeWidgetToDataSource(QString, QString);
    void unscribeWidgetToDataSource(QString, QString);

private:
    ICommunicator *mCommunicator;
    Parser *mParser;
};

