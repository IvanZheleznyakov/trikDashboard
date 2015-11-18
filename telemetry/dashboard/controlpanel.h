#pragma once
#include "../telemetry_const.h"

#include <QMainWindow>
#include <QDockWidget>
#include "sensor.h"
#include <QTranslator>

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
    QTranslator appTranslator;

    void changeEvent(QEvent *event);

signals:
    void newConnection();
    void lostConnection();
    void setConnection(QString ip, int port);

public slots:
    void setStatusBarText(const QString text);

protected:
    void showEvent(QShowEvent *event);

private slots:
    void retranslateUi();
    void createDockWidget(QDockWidget* dw);

private:
    ToolBar *toolBar;
};
