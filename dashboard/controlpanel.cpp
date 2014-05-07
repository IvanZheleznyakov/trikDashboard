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

    connect(toolBar->accelAction, SIGNAL(triggered()), this, SLOT(createDockWidget()));

}

void ControlPanel::setStatusBarText(const QString text)
{
    statusBar()->showMessage(text.trimmed().toLatin1());
}

void ControlPanel::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
}

void ControlPanel::createDockWidget()
{
    QDockWidget *dw = new QDockWidget();
    QAction* action = (QAction*)sender();
    dw->setObjectName(action->text());
    dw->setFeatures(dw->features() | QDockWidget::DockWidgetClosable);
    dw->setFeatures(dw->features() | QDockWidget::DockWidgetMovable);
    dw->setFeatures(dw->features() | QDockWidget::DockWidgetFloatable);
    dw->setAllowedAreas(Qt::AllDockWidgetAreas);
    dw->setWindowTitle(action->text());
    dw->setWidget(new QTextEdit);
    //dw->setWidget(new CustomPlotWidget(3, action->text()));

    addDockWidget(Qt::TopDockWidgetArea, dw);
    //connect(dw->closeEvent(), SIGNAL(triggered(bool)) , this, SLOT(destroyDockWidget()));
    widgets.append(dw);
}

void ControlPanel::destroyDockWidget()
{
 //   int index = destroyDockWidgetMenu->actions().indexOf(action);
  //  delete widgets.takeAt(index);
    //QDockWidget *dw = (QDockWidget*) sender();
    //action->deleteLater();
    qDebug()<<"delete";
}
