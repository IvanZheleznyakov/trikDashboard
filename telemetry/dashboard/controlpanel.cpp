#include "controlpanel.h"
#include "toolbar.h"

#include <QAction>
#include <QMenu>
#include <QStatusBar>
#include <QApplication>
#include <qdebug.h>


Q_DECLARE_METATYPE(QDockWidget::DockWidgetFeatures)

ControlPanel::ControlPanel(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{

    qApp->installTranslator(&appTranslator);

    accelerometer = new Sensor(TelemetryConst::ACCELEROMETER_TITLE(), ACCELEROMETER_NAME);
    gyroscope = new Sensor(TelemetryConst::GYROSCOPE_TITLE(), GYROSCOPE_NAME);
    battery = new Sensor(TelemetryConst::BATTERY_TITLE(), BATTERY_NAME);
    powerMotor1 = new Sensor(TelemetryConst::POWER_MOTOR1_TITLE(), POWER_MOTOR1_NAME);
    powerMotor2 = new Sensor(TelemetryConst::POWER_MOTOR2_TITLE(), POWER_MOTOR2_NAME);
    powerMotor3 = new Sensor(TelemetryConst::POWER_MOTOR3_TITLE(), POWER_MOTOR3_NAME);
    powerMotor4 = new Sensor(TelemetryConst::POWER_MOTOR4_TITLE(), POWER_MOTOR4_NAME);

    sensors << accelerometer << gyroscope << battery << powerMotor1 << powerMotor2 << powerMotor3 << powerMotor4;
    foreach (Sensor* s, sensors) {
        connect(s,SIGNAL(newDockWidget(DockWidget*)), this, SLOT(createDockWidget(DockWidget*)));
    }

    toolBar = new ToolBar(this);
    connect(toolBar, SIGNAL(setConnection(QString,int)), this, SIGNAL(setConnection(QString, int)));
    connect(this,SIGNAL(newConnection()),toolBar,SLOT(insertTelemetry()));
    connect(this,SIGNAL(lostConnection()),toolBar,SLOT(deleteTelemetry()));
    addToolBar(Qt::LeftToolBarArea, toolBar);

    DockOptions opts;
    opts |= AllowNestedDocks;
    opts |= AnimatedDocks;
    QMainWindow::setDockOptions(opts);

    QAction *viewAction = toolBar->toggleViewAction();
    viewAction->setShortcut(SHOW_HIDE_SHORTCUT);
    addAction(viewAction);

    retranslateUi();
}

void ControlPanel::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        retranslateUi();
    }
    QMainWindow::changeEvent(event);
}

void ControlPanel::retranslateUi()
{
    statusBar()->showMessage(TelemetryConst::SHOW_HIDE_TEXT());
    setWindowTitle(tr("TRIK Telemetry Dashboard"));

    accelerometer->setTitle(TelemetryConst::ACCELEROMETER_TITLE());
    gyroscope->setTitle(TelemetryConst::GYROSCOPE_TITLE());
    battery->setTitle(TelemetryConst::BATTERY_TITLE());
    powerMotor1->setTitle(TelemetryConst::POWER_MOTOR1_TITLE());
    powerMotor2->setTitle(TelemetryConst::POWER_MOTOR2_TITLE());
    powerMotor3->setTitle(TelemetryConst::POWER_MOTOR3_TITLE());
    powerMotor4->setTitle(TelemetryConst::POWER_MOTOR4_TITLE());

    foreach (Sensor* s, sensors) {
        s->retranslateUi();
    }
}

void ControlPanel::setStatusBarText(const QString text)
{
    statusBar()->showMessage(text.trimmed());
}

void ControlPanel::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
}

void ControlPanel::createDockWidget(DockWidget* dw)
{
    addDockWidget(Qt::LeftDockWidgetArea, dw);
}
