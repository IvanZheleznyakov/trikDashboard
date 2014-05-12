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
    if (name == ACCELEROMETER_NAME || name == GYROSCOPE_NAME)
    {
        pWidget = new CustomPlotWidget(3, name);
    } else
    {
        pWidget = new EmptyWidget(name);
    }
}

void Sensor::actionTriggered()
{
    pActive = !pActive;
    if (pActive)
    {
        setActive();
    } else
    {
        setInactive();
    }
}

void Sensor::setActive()
{
    QString buf = SUBSCRIBE_STRING + name;
    emit command(buf);

    createDashboardWidget();

    dockWidget = new QDockWidget();
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
