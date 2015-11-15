#include "sensor.h"
#include <QTextEdit>

Sensor::Sensor(QString title, QString devName, QObject *parent) :
    QObject(parent),
    pActive(false),
    title(title),
    devName(devName)
{
    sensorButton = new QPushButton();
    sensorButton->setStyleSheet("QPushButton { background-color: rgb(170, 170, 170); border-style: outset; border-width: 0.5px; border-radius: 5px; border-color: beige; padding: 4px;}"
                         "QPushButton:pressed { background-color: rgb(200, 200, 200); border-style: inset; }");

    connect(sensorButton, SIGNAL(clicked()), this, SLOT(actionTriggered()));

    retranslateUi();
}

void Sensor::retranslateUi()
{
    sensorButton->setText(title);
}

void Sensor::createDashboardWidgets()
{
    if (title == TelemetryConst::ACCELEROMETER_TITLE()
            || title == TelemetryConst::GYROSCOPE_TITLE())
    {

        pWidgets.append(new CustomPlotWidget(3, title));
        pWidgets.append(new TableWidget(3, title));
    } else
    if (title == TelemetryConst::BATTERY_TITLE())
    {
//        pWidget = new LCDNumberWidget(title);
        pWidgets.append(new TableWidget(1, title));
    } else
    if (title == TelemetryConst::POWER_MOTOR1_TITLE()
            || title == TelemetryConst::POWER_MOTOR2_TITLE()
            || title == TelemetryConst::POWER_MOTOR3_TITLE()
            || title == TelemetryConst::POWER_MOTOR4_TITLE())
    {
        pWidgets.append(new ProgressBarWidget(title));
    } else
    {
        pWidgets.append(new EmptyWidget(title));
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

    createDashboardWidgets();

    dockWidget = new DockWidget(this);
    dockWidget->setObjectName(title);
    dockWidget->setFeatures(dockWidget->features() | QDockWidget::DockWidgetClosable);
    dockWidget->setFeatures(dockWidget->features() | QDockWidget::DockWidgetMovable);
    dockWidget->setFeatures(dockWidget->features() | QDockWidget::DockWidgetFloatable);
    dockWidget->setAllowedAreas(Qt::AllDockWidgetAreas);
    dockWidget->setWindowTitle(title);
    foreach (DashboardWidget *widget, pWidgets) {
        dockWidget->setWidget(widget);
    }

//    dockWidget->setWidget(pWidget);

    emit newDockWidget(dockWidget);

    foreach (DashboardWidget *widget, pWidgets) {
        widget->startPaint();
    }

//    pWidget->startPaint();
}

void Sensor::setInactive()
{
    pActive = false;
    QString buf = UNSUBSCRIBE_STRING +":"+ devName;
    emit command(buf);
    foreach (DashboardWidget *widget, pWidgets) {
        widget->stopPaint();
    }

//    pWidget->stopPaint();
    dockWidget->deleteLater();
    foreach (DashboardWidget *widget, pWidgets) {
        widget->deleteLater();
    }

//    pWidget->deleteLater();
}

void Sensor::setTitle(QString newTitle)
{
    title = newTitle;
}

QString Sensor::getTitle()
{
    return title;
}

bool Sensor::active()
{
    return pActive;
}

QVector<DashboardWidget*> Sensor::widgets()
{
    return pWidgets;
}

QPushButton* Sensor::button()
{
    return sensorButton;
}
