#include "parser.h"
#include "elementarydatasource.h"
#include "compositedatasource.h"
#include <QStringList>
#include <QVector>

#include <QDebug>

Parser::Parser()
{
    connect(this, &Parser::messageIsParsed, this, &Parser::sendData);
}

void Parser::parseMessage(QString message)
{
    if (message != "TRIK connected")
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

            QString deviceName = info.at(0);

            if (deviceName == ACCELEROMETER_NAME) {
                deviceName = TelemetryConst::ACCELEROMETER_TITLE();
            } else if (deviceName == GYROSCOPE_NAME) {
                deviceName = TelemetryConst::GYROSCOPE_TITLE();
            } else if (deviceName == POWER_MOTOR1_NAME) {
                deviceName = TelemetryConst::POWER_MOTOR1_TITLE();
            } else if (deviceName == POWER_MOTOR2_NAME) {
                deviceName = TelemetryConst::POWER_MOTOR2_TITLE();
            } else if (deviceName == POWER_MOTOR3_NAME) {
                deviceName = TelemetryConst::POWER_MOTOR3_TITLE();
            } else if (deviceName == POWER_MOTOR4_NAME) {
                deviceName = TelemetryConst::POWER_MOTOR4_TITLE();
            } else if (deviceName == BATTERY_NAME) {
                deviceName = TelemetryConst::BATTERY_TITLE();
            }

            if (!mMap.contains(deviceName)) {
                ElementaryDataSource *newDataSource = new ElementaryDataSource(deviceName);

                addDataSource(deviceName, newDataSource);
            }

            emit messageIsParsed(deviceName, values);
        }
    }
}

void Parser::parseExpression(QString name, QString expression)
{
        if (!mMap.contains(name))
        {
            QVector<IDataSource *> dataSources;
            if ((expression.contains(ACCELEROMETER_NAME_FIRST) || expression.contains(ACCELEROMETER_NAME_SECOND) || expression.contains(ACCELEROMETER_NAME_THIRD)) && mMap.contains(TelemetryConst::ACCELEROMETER_TITLE()))
            {
                dataSources.append(mMap[TelemetryConst::ACCELEROMETER_TITLE()]);
                qDebug() << "a yes" << endl;
            }
            if ((expression.contains(GYROSCOPE_NAME_FIRST) || expression.contains(GYROSCOPE_NAME_SECOND) || expression.contains(GYROSCOPE_NAME_THIRD)) && mMap.contains(TelemetryConst::GYROSCOPE_TITLE()))
            {
                dataSources.append(mMap[TelemetryConst::GYROSCOPE_TITLE()]);
            }
            if (expression.contains(BATTERY_NAME) && mMap.contains(TelemetryConst::BATTERY_TITLE()))
            {
                dataSources.append(mMap[TelemetryConst::BATTERY_TITLE()]);
                qDebug() << "b yes" << endl;
            }
            if (expression.contains(POWER_MOTOR1_NAME) && mMap.contains(TelemetryConst::POWER_MOTOR1_TITLE()))
            {
                dataSources.append(mMap[TelemetryConst::POWER_MOTOR1_TITLE()]);
            }
            if (expression.contains(POWER_MOTOR2_NAME) && mMap.contains(TelemetryConst::POWER_MOTOR2_TITLE()))
            {
                dataSources.append(mMap[TelemetryConst::POWER_MOTOR2_TITLE()]);
            }
            if (expression.contains(POWER_MOTOR3_NAME) && mMap.contains(TelemetryConst::POWER_MOTOR3_TITLE()))
            {
                dataSources.append(mMap[TelemetryConst::POWER_MOTOR3_TITLE()]);
            }
            if (expression.contains(POWER_MOTOR4_NAME) && mMap.contains(TelemetryConst::POWER_MOTOR4_TITLE()))
            {
                dataSources.append(mMap[TelemetryConst::POWER_MOTOR4_TITLE()]);
            }
            CompositeDataSource *newDataSource = new CompositeDataSource(name, expression, dataSources);
            connect(newDataSource, &CompositeDataSource::refreshData, this, &Parser::parseExpression);

            addDataSource(name, newDataSource);
        }

        QVector<float> values = expressionParser.parseExpression(mMap, expression);

        emit messageIsParsed(name, values);
}

void Parser::sendData(QString deviceName, QVector<float> values)
{
    mMap[deviceName]->updateData(values);
}

void Parser::addDataSource(QString deviceName, IDataSource *newDataSource)
{
    if (!mMap.contains(deviceName)) {
        mMap.insert(deviceName, newDataSource);
    }
}

void Parser::requestDataToSubscribe(QString widgetName, QString deviceName)
{
    if (mMap.contains(deviceName))
    {
        emit subscribeWidgetToDataSource(mMap[deviceName], widgetName, deviceName);
    }
}

void Parser::requestDataToUnscribe(QString widgetName, QString deviceName)
{
    emit unscribeWidgetFromDataSource(mMap[deviceName], widgetName, deviceName);
}
