#include "parser.h"
#include "elementarydatasource.h"
#include <QStringList>
#include <QVector>
#include <QtScript/QScriptEngine>

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
                ElementaryDataSource *newDataSource = new ElementaryDataSource();

                addDataSource(deviceName, newDataSource);
            }

            emit messageIsParsed(deviceName, values);
        }
    }
}

void Parser::parseExpression(QString name, QString expression)
{
    expression = "";
    //Подготовка
        double x=2;//в какой точки ищем значение функции
        QString CodeFunction="RESULT = Math.sin(x);RESULT = RESULT + 1;";

        //Необходимые переменные
        double Result;
        QScriptEngine engine;
        QScriptValue scriptFun;

        //подготовка движка QtScript
        engine.evaluate("function fun(x)\n {\n var RESULT=0;\n"+CodeFunction+"\n return RESULT;\n}\n");
        scriptFun = engine.globalObject().property("fun");

        //Вычисление значения функции в точке
        Result = scriptFun.call(QScriptValue(), QScriptValueList() << x).toNumber();
        QVector<float> values;
        values << Result << 0.0 << 0.0;

        if (!mMap.contains(name))
        {
            ElementaryDataSource *newDataSource = new ElementaryDataSource();

            addDataSource(name, newDataSource);
        }

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
