#include "expressionparser.h"

#include <QtScript/QScriptEngine>
#include "telemetry_const.h"

ExpressionParser::ExpressionParser()
{

}

QVector<float> ExpressionParser::parseExpression(QMap<QString, IDataSource *> map, QString expression)
{
    double A1 = 0;
    double A2 = 0;
    double A3 = 0;
    if (map.contains(TelemetryConst::ACCELEROMETER_TITLE()))
    {
        A1 = map[TelemetryConst::ACCELEROMETER_TITLE()]->getData().at(0);
        A2 = map[TelemetryConst::ACCELEROMETER_TITLE()]->getData().at(1);
        A3 = map[TelemetryConst::ACCELEROMETER_TITLE()]->getData().at(2);
    }
    double G1 = 0;
    double G2 = 0;
    double G3 = 0;
    if (map.contains(TelemetryConst::GYROSCOPE_TITLE()))
    {
        G1 = map[TelemetryConst::GYROSCOPE_TITLE()]->getData().at(0);
        G2 = map[TelemetryConst::GYROSCOPE_TITLE()]->getData().at(1);
        G3 = map[TelemetryConst::GYROSCOPE_TITLE()]->getData().at(2);
    }
    double B = 0;
    double M1 = 0;
    double M2 = 0;
    double M3 = 0;
    double M4 = 0;
    if (map.contains(TelemetryConst::BATTERY_TITLE()))
    {
        B = map[TelemetryConst::BATTERY_TITLE()]->getData().at(0);
    }
    if (map.contains(TelemetryConst::POWER_MOTOR1_TITLE()))
    {
        M1 = map[TelemetryConst::POWER_MOTOR1_TITLE()]->getData().at(0);
    }
    if (map.contains(TelemetryConst::POWER_MOTOR2_TITLE()))
    {
        M2 = map[TelemetryConst::POWER_MOTOR2_TITLE()]->getData().at(0);
    }
    if (map.contains(TelemetryConst::POWER_MOTOR3_TITLE()))
    {
        M3 = map[TelemetryConst::POWER_MOTOR3_TITLE()]->getData().at(0);
    }
    if (map.contains(TelemetryConst::POWER_MOTOR4_TITLE()))
    {
        M4 = map[TelemetryConst::POWER_MOTOR4_TITLE()]->getData().at(0);
    }

    QString CodeFunction = "RESULT = " + expression + ";";

    double Result;
    QScriptEngine engine;
    QScriptValue scriptFun;

    engine.evaluate("function fun(A1, A2, A3, G1, G2, G3, B, M1, M2, M3, M4)\n {\n var RESULT=0;\n"+CodeFunction+"\n return RESULT;\n}\n");
    scriptFun = engine.globalObject().property("fun");

    Result = scriptFun.call(QScriptValue(), QScriptValueList() << A1 << A2 << A3 << G1 << G2 << G3 << B << M1 << M2 << M3 << M4).toNumber();
    QVector<float> values;
    values << Result;

    return values;
}
