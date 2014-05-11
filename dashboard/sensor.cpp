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
    if (name == "Accelerometer" || name == "Gyroscope")
    {
        pWidget = new EmptyWidget(name);
    } else
    {
        //pWidget = new QTextEdit(); Template!!!
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
    QString buf = "subscribe:"+name;
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

    //start widget;
    emit newDockWidget(dockWidget);

}

void Sensor::setInactive()
{
    QString buf = "unsubscribe:"+name;
    emit command(buf);
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
