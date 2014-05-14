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
    Sensor* accelerometer;
    Sensor* gyroscope;

signals:
    void newConnection();
    void lostConnection();
    void setConnection(QString ip, int port);

public slots:
    void setStatusBarText(const QString text);

protected:
    void showEvent(QShowEvent *event);

public slots:
    void createDockWidget(QDockWidget* dw);

private:
    ToolBar *toolBar;

};
