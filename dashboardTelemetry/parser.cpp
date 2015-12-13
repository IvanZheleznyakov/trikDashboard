#include "parser.h"
#include <QStringList>
#include <QVector>

Parser::Parser()
{

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

        if (map.contains(deviceName)) {
            map[deviceName]->readData(values);
        } else {

        }

/*        if (deviceName == ACCELEROMETER_NAME && panel.accelerometer->active())
        {
            foreach (DashboardWidget *widget, panel.accelerometer->widgets()) {
                widget->updateData(values);
            }

            emit panel.accelerometer->newData(values);
//            panel.accelerometer->widget()->updateData(values);
        } else
        if (deviceName == GYROSCOPE_NAME && panel.gyroscope->active())
        {
            foreach (DashboardWidget *widget, panel.gyroscope->widgets()) {
                widget->updateData(values);
            }

            emit panel.gyroscope->newData(values);
//            panel.gyroscope->widget()->updateData(values);
        } else
        if (deviceName == POWER_MOTOR1_NAME && panel.powerMotor1->active())
        {
            foreach (DashboardWidget *widget, panel.powerMotor1->widgets()) {
                widget->updateData(values);
            }

            emit panel.powerMotor1->newData(values);
//            panel.powerMotor1->widget()->updateData(values);
        } else
        if (deviceName == POWER_MOTOR2_NAME && panel.powerMotor2->active())
        {
            foreach (DashboardWidget *widget, panel.powerMotor2->widgets()) {
                widget->updateData(values);
            }

            emit panel.powerMotor2->newData(values);
//            panel.powerMotor2->widget()->updateData(values);
        } else
        if (deviceName == POWER_MOTOR3_NAME && panel.powerMotor3->active())
        {
            foreach (DashboardWidget *widget, panel.powerMotor3->widgets()) {
                widget->updateData(values);
            }

            emit panel.powerMotor3->newData(values);
//            panel.powerMotor3->widget()->updateData(values);
        } else
        if (deviceName == POWER_MOTOR4_NAME && panel.powerMotor4->active())
        {
            foreach (DashboardWidget *widget, panel.powerMotor4->widgets()) {
                widget->updateData(values);
            }

            emit panel.powerMotor4->newData(values);
//            panel.powerMotor4->widget()->updateData(values);
        } else
        if (deviceName == BATTERY_NAME && panel.battery->active())
        {
            foreach (DashboardWidget *widget, panel.battery->widgets()) {
                widget->updateData(values);
            }

            emit panel.battery->newData(values);
   //         panel.battery->widget()->updateData(values);
        }
   */ }
}

void Parser::sendData(QString deviceName, QVector<float> values)
{

}
