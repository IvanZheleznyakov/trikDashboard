#include "emptywidget.h"
#include <QTextEdit>

EmptyWidget::EmptyWidget(QString title, int timerInterval) :
    DashboardWidget(1, title, timerInterval)
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
