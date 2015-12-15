#pragma once

#include "icommunicator.h"
#include "parser.h"

#include <QObject>

class IDataSource;
class Facade : public QObject
{
    Q_OBJECT

public:
    Facade(ICommunicator *mCommunicator);
    bool connectToTRIK(QString ip, int port);

signals:
    void subscribeWidgetToDataSource(IDataSource *, QString, QString);

public slots:
    void requestDataToSubscribe(QString widgetName, QString deviceName);
    void requestDataToUnscribe(QString, QString);

private:
    ICommunicator *mCommunicator;
    Parser *mParser;
};

