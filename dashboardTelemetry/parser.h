#pragma once

#include <QObject>
#include <QMap>
#include <QVector>
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
    void messageIsParsed(QString, QVector<float>);

private slots:
    void sendData(QString deviceName, QVector<float> values);
    void addDataSource(QString deviceName, IDataSource *newDataSource);

private:
    QMap<QString, IDataSource *> mMap;
};

