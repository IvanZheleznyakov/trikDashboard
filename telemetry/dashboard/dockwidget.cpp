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

void DockWidget::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        this->setWindowTitle(sensor->getTitle());
    }
    QDockWidget::changeEvent(event);
}
