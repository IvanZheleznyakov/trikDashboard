#include "emptywidget.h"
#include <QTextEdit>

EmptyWidget::EmptyWidget(QString title) :
    DashboardWidget(1, title)
{
    connect(paintTimer, &QTimer::timeout, this, &EmptyWidget::paintWidget);

    layout->addWidget(new QTextEdit());
    setLayout(layout);
}


void EmptyWidget::init()
{
}

void EmptyWidget::paintWidget()
{
}
