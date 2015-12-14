#include "controlpanel.h"

#include "customplotwidget.h"
#include "lcdnumberwidget.h"
#include "progressbarwidget.h"
#include "tablewidget.h"

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

    mToolBar = new ToolBar();
    connect(mToolBar, &ToolBar::setConnection, this, &ControlPanel::setConnection);
    connect(this, &ControlPanel::newConnection, mToolBar, &ToolBar::insertTelemetry);
    connect(this, &ControlPanel::lostConnection, mToolBar, &ToolBar::deleteTelemetry);
    connect(mToolBar, &ToolBar::subscribeWidgetToDataSource, this, &ControlPanel::createSensorWidget);
    connect(mToolBar, &ToolBar::unscribeWidgetToDataSource, this, &ControlPanel::deleteSensorWidget);
    connect(mToolBar, &ToolBar::subscribeWidgetToDataSource, this, &ControlPanel::subscribeWidgetToDataSource);
    connect(mToolBar, &ToolBar::unscribeWidgetToDataSource, this, &ControlPanel::unscribeWidgetToDataSource);
    addToolBar(Qt::LeftToolBarArea, mToolBar);

    DockOptions opts;
    opts |= AllowNestedDocks;
    opts |= AnimatedDocks;
    QMainWindow::setDockOptions(opts);

    QAction *viewAction = mToolBar->toggleViewAction();
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
}

void ControlPanel::setStatusBarText(const QString text)
{
    statusBar()->showMessage(text.trimmed());
}

void ControlPanel::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
}

void ControlPanel::createSensorWidget(QString widgetName, QString sensorName)
{
    QDockWidget *dockWidget = new QDockWidget();
    QString nameOfDockWidget = sensorName + ": " + widgetName;
    dockWidget->setObjectName(nameOfDockWidget);
    dockWidget->setFeatures(dockWidget->features() | QDockWidget::DockWidgetClosable);
    dockWidget->setFeatures(dockWidget->features() | QDockWidget::DockWidgetMovable);
    dockWidget->setFeatures(dockWidget->features() | QDockWidget::DockWidgetFloatable);
    dockWidget->setAllowedAreas(Qt::AllDockWidgetAreas);
    dockWidget->setWindowTitle(nameOfDockWidget);
    QPair<QDockWidget *, ISensorWidget *> newPair;
    newPair.first = dockWidget;
    if (widgetName == TelemetryConst::TABLE_TITLE()) {
        newPair.second = new TableWidget(3, nameOfDockWidget, SENSORS3D_DATA_UPDATE_PERIOD);
    } else if (widgetName == TelemetryConst::PLOT_TITLE()) {
        newPair.second = new CustomPlotWidget(3, nameOfDockWidget, SENSORS3D_DATA_UPDATE_PERIOD);
    } else if (widgetName == TelemetryConst::LCDNUMBER_TITLE()) {
        newPair.second = new LCDNumberWidget(nameOfDockWidget, BATTERY_DATA_UPDATE_PERIOD);
    } else if (widgetName == TelemetryConst::PROGRESSBAR_TITLE()) {
        newPair.second = new ProgressBarWidget(nameOfDockWidget, MOTOR_DATA_UPDATE_PERIOD);
    }

    newPair.first->setWidget(newPair.second);
    mWidgets.insert(nameOfDockWidget, newPair);
    createDockWidget(newPair.first);
}

void ControlPanel::createDockWidget(QDockWidget* dw)
{
    addDockWidget(Qt::LeftDockWidgetArea, dw);
}

void ControlPanel::deleteSensorWidget(QString widgetName, QString sensorName)
{
    QString nameOfWidget = sensorName + ": " + widgetName;
    mWidgets[nameOfWidget].second->stopPaint();
    mWidgets[nameOfWidget].first->deleteLater();
    mWidgets[nameOfWidget].second->deleteLater();
    mWidgets.remove(nameOfWidget);
}
