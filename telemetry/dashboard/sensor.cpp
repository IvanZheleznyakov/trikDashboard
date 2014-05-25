#include "sensor.h"
#include <QTextEdit>

Sensor::Sensor(QString title, QString devName, QObject *parent) :
    QObject(parent),
    pActive(false),
    title(title),
    devName(devName)
{
    sensorButton = new QPushButton(title);
    sensorButton->setStyleSheet("QPushButton { background-color: rgb(170, 170, 170); border-style: outset; border-width: 0.5px; border-radius: 5px; border-color: beige; padding: 4px;}"
                         "QPushButton:pressed { background-color: rgb(200, 200, 200); border-style: inset; }");

    connect(sensorButton, SIGNAL(clicked()), this, SLOT(actionTriggered()));
}

void Sensor::createDashboardWidget()
{
    if (title == TelemetryConst::ACCELEROMETER_TITLE()
            || title == TelemetryConst::GYROSCOPE_TITLE())
    {
        pWidget = new CustomPlotWidget(3, title);
    } else
    if (title == TelemetryConst::BATTERY_TITLE())
    {
        pWidget = new LCDNumberWidget(title);
    } else
    if (title == TelemetryConst::POWER_MOTOR1_TITLE()
            || title == TelemetryConst::POWER_MOTOR2_TITLE()
            || title == TelemetryConst::POWER_MOTOR3_TITLE()
            || title == TelemetryConst::POWER_MOTOR4_TITLE())
    {
        pWidget = new ProgressBarWidget(title);
    } else
    {
        pWidget = new EmptyWidget(title);
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
    QString buf = SUBSCRIBE_STRING +":"+ devName;
    emit command(buf);

    createDashboardWidget();

    dockWidget = new DockWidget(this);
    dockWidget->setObjectName(title);
    dockWidget->setFeatures(dockWidget->features() | QDockWidget::DockWidgetClosable);
    dockWidget->setFeatures(dockWidget->features() | QDockWidget::DockWidgetMovable);
    dockWidget->setFeatures(dockWidget->features() | QDockWidget::DockWidgetFloatable);
    dockWidget->setAllowedAreas(Qt::AllDockWidgetAreas);
    dockWidget->setWindowTitle(title);
    dockWidget->setWidget(pWidget);

    emit newDockWidget(dockWidget);

    pWidget->startPaint();
}

void Sensor::setInactive()
{
    pActive = false;
    QString buf = UNSUBSCRIBE_STRING +":"+ devName;
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
