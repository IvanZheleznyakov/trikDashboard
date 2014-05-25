#pragma once
#include "../telemetry_const.h"

#include <QMainWindow>
#include <QDockWidget>
#include "sensor.h"

class ToolBar;
class ControlPanel : public QMainWindow
{
    Q_OBJECT
public:
    ControlPanel(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    QVector<Sensor*> sensors;
    Sensor* accelerometer;
    Sensor* gyroscope;
    Sensor* battery;
    Sensor* powerMotor1;
    Sensor* powerMotor2;
    Sensor* powerMotor3;
    Sensor* powerMotor4;
    Sensor* encoder2;
    Sensor* encoder3;
    Sensor* encoder4;

signals:
    void newConnection();
    void lostConnection();
    void setConnection(QString ip, int port);

public slots:
    void setStatusBarText(const QString text);

protected:
    void showEvent(QShowEvent *event);

public slots:
    void createDockWidget(DockWidget* dw);

private:
    ToolBar *toolBar;
};
