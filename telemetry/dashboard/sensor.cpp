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

    alert = new Alert(title);

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

        pWidgets.second.append(new CustomPlotWidget(3, title, SENSORS3D_DATA_UPDATE_PERIOD));
        pWidgets.second.append(new TableWidget(3, title, SENSORS3D_DATA_UPDATE_PERIOD));
    } else
    if (title == TelemetryConst::BATTERY_TITLE())
    {
        pWidgets.second.append(new LCDNumberWidget(title, BATTERY_DATA_UPDATE_PERIOD));
        pWidgets.second.append(new TableWidget(1, title, BATTERY_DATA_UPDATE_PERIOD));
    } else
    if (title == TelemetryConst::POWER_MOTOR1_TITLE()
            || title == TelemetryConst::POWER_MOTOR2_TITLE()
            || title == TelemetryConst::POWER_MOTOR3_TITLE()
            || title == TelemetryConst::POWER_MOTOR4_TITLE())
    {
        pWidgets.second.append(new ProgressBarWidget(title, MOTOR_DATA_UPDATE_PERIOD));
        pWidgets.second.append(new TableWidget(1, title, MOTOR_DATA_UPDATE_PERIOD));
    } else
    {
        pWidgets.second.append(new EmptyWidget(title, 0));
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

    for (int i = 0; i != pWidgets.second.count(); ++i)
    {
        DockWidget *dockWidget = new DockWidget(this);
        dockWidget->setObjectName(title);
        dockWidget->setFeatures(dockWidget->features() | QDockWidget::DockWidgetClosable);
        dockWidget->setFeatures(dockWidget->features() | QDockWidget::DockWidgetMovable);
        dockWidget->setFeatures(dockWidget->features() | QDockWidget::DockWidgetFloatable);
        dockWidget->setAllowedAreas(Qt::AllDockWidgetAreas);
        dockWidget->setWindowTitle(title);
        pWidgets.first.append(dockWidget);
    }

    for (int i = 0; i != pWidgets.first.count(); ++i) {
        pWidgets.first.at(i)->setWidget(pWidgets.second.at(i));
        emit newDockWidget(pWidgets.first.at(i));
    }

//    dockWidget->setWidget(pWidget);

    foreach (DashboardWidget *widget, pWidgets.second) {
        widget->startPaint();
    }

//    pWidget->startPaint();
}

void Sensor::setInactive()
{
    pActive = false;
    QString buf = UNSUBSCRIBE_STRING +":"+ devName;
    emit command(buf);
//    foreach (DashboardWidget *widget, pWidgets.second) {
//        widget->stopPaint();
//    }

// //    pWidget->stopPaint();

//    foreach (DockWidget *widget, pWidgets.first) {
//        widget->deleteLater();
//    }

//    foreach (DashboardWidget *widget, pWidgets.second) {
//        widget->deleteLater();
//    }

// //    pWidget->deleteLater();
    int numOfWidgets = pWidgets.first.count();
    for (int i = 0; i != numOfWidgets; ++i) {
        pWidgets.second.at(i)->stopPaint();
        pWidgets.first.at(i)->deleteLater();
        pWidgets.second.at(i)->deleteLater();
        // Do I need to delete widgets with operator delete?
    }

    pWidgets.first.clear();
    pWidgets.second.clear();
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
    return pWidgets.second;
}

QPushButton* Sensor::button()
{
    return sensorButton;
}

QPushButton *Sensor::alertButton()
{
    return alert->button();
}
