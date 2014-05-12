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
    accelerometer = new Sensor(ACCELEROMETER_NAME);
    connect(accelerometer, SIGNAL(newDockWidget(QDockWidget*)), this, SLOT(createDockWidget(QDockWidget*)));
    gyroscope = new Sensor(GYROSCOPE_NAME);
    connect(gyroscope,SIGNAL(newDockWidget(QDockWidget*)), this, SLOT(createDockWidget(QDockWidget*)));

    setWindowTitle("TRIK Telemetry Dashboard");
    toolBar = new ToolBar(this);
    connect(toolBar, SIGNAL(setConnection(QString,int)), this, SIGNAL(setConnection(QString, int)));
    connect(this,SIGNAL(newConnection()),toolBar,SLOT(insertTelemetry()));
    connect(this,SIGNAL(lostConnection()),toolBar,SLOT(deleteTelemetry()));
    addToolBar(Qt::LeftToolBarArea, toolBar);

    setStatusBarText(SHOW_HIDE_TEXT);

    DockOptions opts;
    opts |= AllowNestedDocks;
    opts |= AnimatedDocks;
    QMainWindow::setDockOptions(opts);

    QAction *viewAction = toolBar->toggleViewAction();
    viewAction->setShortcut(SHOW_HIDE_SHORTCUT);
    addAction(viewAction);
}

void ControlPanel::setStatusBarText(const QString text)
{
    statusBar()->showMessage(text.trimmed().toLatin1());
}

void ControlPanel::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
}

void ControlPanel::createDockWidget(QDockWidget* dw)
{
    addDockWidget(Qt::TopDockWidgetArea, dw);
}
