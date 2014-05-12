#include "emptywidget.h"
#include <QTextEdit>

EmptyWidget::EmptyWidget(QString title) :
    DashboardWidget(1, title)
{
    connect(&paintTimer, SIGNAL(timeout()), this, SLOT(paintWidget()));
    layout->addWidget(new QTextEdit());
    setLayout(layout);
}


void EmptyWidget::init()
{
}

void EmptyWidget::paintWidget()
{
}
