#include "sensor.h"
#include <QTextEdit>

Sensor::Sensor(QString name, QObject *parent) :
    QObject(parent),
    pActive(false),
    name(name)
{
    sensorButton = new QPushButton(name);
    sensorButton->setStyleSheet("QPushButton { background-color: rgb(170, 170, 170); border-style: outset; border-width: 0.5px; border-radius: 5px; border-color: beige; padding: 4px;}"
                         "QPushButton:pressed { background-color: rgb(200, 200, 200); border-style: inset; }");

    connect(sensorButton, SIGNAL(clicked()), this, SLOT(actionTriggered()));
}

void Sensor::createDashboardWidget()
{
    if (name == ACCELEROMETER_TITLE || name == GYROSCOPE_TITLE)
    {
        pWidget = new CustomPlotWidget(3, name);
    } else
    if (name == BATTERY_TITLE || name == POWER_MOTOR1_TITLE)
    {
        pWidget = new LCDNumberWidget(name);
    } else
    {
        pWidget = new EmptyWidget(name);
    }
}

void Sensor::actionTriggered()
{
    if (!pActive)
    {
        setActive();
    } else
    {
        setInactive();
    }
}


void Sensor::setActive()
{
    pActive = true;
    QString buf = SUBSCRIBE_STRING + name;
    emit command(buf);

    createDashboardWidget();

    dockWidget = new DockWidget(this);
    dockWidget->setObjectName(name);
    dockWidget->setFeatures(dockWidget->features() | QDockWidget::DockWidgetClosable);
    dockWidget->setFeatures(dockWidget->features() | QDockWidget::DockWidgetMovable);
    dockWidget->setFeatures(dockWidget->features() | QDockWidget::DockWidgetFloatable);
    dockWidget->setAllowedAreas(Qt::AllDockWidgetAreas);
    dockWidget->setWindowTitle(name);
    dockWidget->setWidget(pWidget);

    emit newDockWidget(dockWidget);

    pWidget->startPaint();
}

void Sensor::setInactive()
{
    pActive = false;
    QString buf = UNSUBSCRIBE_STRING + name;
    emit command(buf);
    pWidget->stopPaint();
    dockWidget->deleteLater();
    pWidget->deleteLater();
}

bool Sensor::active()
{
    return pActive;
}

DashboardWidget* Sensor::widget()
{
    return pWidget;
}

QPushButton* Sensor::button()
{
    return sensorButton;
}
