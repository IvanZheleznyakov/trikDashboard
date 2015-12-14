#include "controlpanel.h"

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

void ControlPanel::createDockWidget(QDockWidget* dw)
{
    addDockWidget(Qt::LeftDockWidgetArea, dw);
}
