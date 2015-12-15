#include "parser.h"
#include "elementarydatasource.h"
#include <QStringList>
#include <QVector>

Parser::Parser()
{
    connect(this, &Parser::messageIsParsed, this, &Parser::sendData);
}

void Parser::parseMessage(QString message)
{
    QStringList devices = message.split(";", QString::SkipEmptyParts);
    for (int i = 0; i != devices.count(); ++i) {
        QStringList info = devices.at(i).split(":", QString::SkipEmptyParts);
        QVector<float> values;
        QStringList data = info.at(1).split("*", QString::SkipEmptyParts);
        for (int j = 0; j != data.count(); ++j) {
            float x = data.at(j).toFloat();
            values << x;
        }

        QString const deviceName = info.at(0);

        if (!mMap.contains(deviceName)) {
            ElementaryDataSource *newDataSource = new ElementaryDataSource();
            addDataSource(deviceName, newDataSource);
            if (deviceName == ACCELEROMETER_NAME) {
                addDataSource(TelemetryConst::ACCELEROMETER_TITLE(), newDataSource);
                emit messageIsParsed(deviceName, values);
            }
        }

//        emit messageIsParsed(deviceName, values);
    }
}

void Parser::sendData(QString deviceName, QVector<float> values)
{
    mMap[deviceName]->updateData(values);
}

void Parser::addDataSource(QString deviceName, IDataSource *newDataSource)
{
    mMap.insert(deviceName, newDataSource);
}

void Parser::requestDataToSubscribe(QString widgetName, QString deviceName)
{
    if (mMap.contains(deviceName))
    {
        emit subscribeWidgetToDataSource(mMap[deviceName], widgetName, deviceName);
    }
}
