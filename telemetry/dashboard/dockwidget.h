#pragma once
#include <../telemetry_const.h>

#include <QDockWidget>
#include "sensor.h"

class Sensor;
class DockWidget : public QDockWidget
{
public:
    DockWidget(Sensor* sensor);
    void closeEvent(QCloseEvent* event);

private:
    Sensor* sensor;
};
