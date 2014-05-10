#include "controlpanel.h"
#include "toolbar.h"

#include <QAction>
#include <QMenu>
#include <QStatusBar>
#include <QApplication>
#include <qdebug.h>
#include <QTextEdit>

Q_DECLARE_METATYPE(QDockWidget::DockWidgetFeatures)

ControlPanel::ControlPanel(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
    accelerometer = new Sensor("Accelerometer");
    connect(accelerometer, SIGNAL(newDockWidget(QDockWidget*)), this, SLOT(createDockWidget(QDockWidget*)));
    gyroscope = new Sensor("Gyroscope");
    connect(gyroscope,SIGNAL(newDockWidget(QDockWidget*)),this,SLOT(createDockWidget(QDockWidget*)));

    setObjectName("MainWindow");
    setWindowTitle("TRIK Telemetry Dashboard");
    toolBar = new ToolBar("Tool Bar", this);
    connect(toolBar, SIGNAL(setConnection(QString,int)), this, SIGNAL(setConnection(QString, int)));
    addToolBar(Qt::LeftToolBarArea, toolBar);

    setStatusBarText("Ready");

    DockOptions opts;
    opts |= AllowNestedDocks;
    opts |= AnimatedDocks;
    QMainWindow::setDockOptions(opts);

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
