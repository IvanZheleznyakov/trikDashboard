#include "dockwidget.h"

DockWidget::DockWidget(Sensor* s): QDockWidget()
{
    sensor = s;
}

void DockWidget::closeEvent(QCloseEvent *event)
{
    sensor->setInactive();
    QDockWidget::closeEvent(event);
}
