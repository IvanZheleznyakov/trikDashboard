#pragma once

#include <QObject>
#include <QMap>
#include "idatasource.h"
#include "telemetry_const.h"

class Parser : public QObject
{
    Q_OBJECT

public:
    Parser();

public slots:
    void parseMessage(QString message);

signals:


private:
    QMap<QString, IDataSource> map;
};

