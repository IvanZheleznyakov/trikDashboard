#include "dashboard.h"
#include <QThread>

Dashboard::Dashboard():
    hi(false)
{
    connect(&tcpCommunicator, SIGNAL(recieveMessage(QString)), this, SLOT(parseMessage(QString)));
    connect(&panel, SIGNAL(setConnection(QString,int)), this, SLOT( connectToTRIK(QString,int)) );
    connect(&tcpCommunicator, SIGNAL(newConnection()), &panel, SIGNAL(newConnection()));
    connect(&tcpCommunicator, SIGNAL(lostConnection()), &panel, SIGNAL(lostConnection()));

    panel.resize(PANEL_START_SIZE);
    panel.setMinimumSize(PANEL_MIN_SIZE);
    panel.show();
}

void Dashboard::connectToTRIK(QString ip, int port)
{
    tcpCommunicator.setIP(ip.toLatin1());
    tcpCommunicator.setPort(port);
    tcpCommunicator.connectToHost();

    panel.setStatusBarText(TelemetryConst::WAITING_RESPONSE_MESSAGE());
    tcpCommunicator.send(SEND_MESSAGE);

    QThread::msleep(WAITING_RESPONSE_TIME);

    if (tcpCommunicator.connectedState() == QTcpSocket::ConnectedState)
    {
        foreach (Sensor* s, panel.sensors) {
            connect(s, SIGNAL(command(QString)), this, SLOT(sendCommand(QString)));
        }
    } else {
        panel.setStatusBarText(TelemetryConst::NOCONNECTION_MESSAGE());
    }
}

void Dashboard::parseMessage(QString message)
{
    if (!hi)
    {
        hi = true;
        panel.setStatusBarText(message);
        return;
    }
    /*
    qDebug() << "receive: " << message;
    panel.setStatusBarText(message);
    */
    QStringList devices = message.split(";", QString::SkipEmptyParts);
    foreach (QString device, devices)
    {
        QStringList info = device.split(":", QString::SkipEmptyParts);
        QVector<float> values;
        QStringList data = info.at(1).split("*", QString::SkipEmptyParts);
        foreach (QString val, data)
        {
            float x = val.toFloat();
            values << x;
        }
        QString const deviceName = info.at(0);

        if (deviceName == ACCELEROMETER_NAME && panel.accelerometer->active())
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
    }
}

void Dashboard::sendCommand(QString command)
{
    //qDebug() <<"send: " << command;
    tcpCommunicator.send(command);
}

