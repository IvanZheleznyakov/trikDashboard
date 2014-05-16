#include "lcdnumberwidget.h"

LCDNumberWidget::LCDNumberWidget(QString title) :
    DashboardWidget(1, title)
{
    connect(paintTimer, &QTimer::timeout, this, &LCDNumberWidget::paintWidget);
    LCDNumbers = new QLCDNumber();

    this->setInterval(1000);
    init();

    layout->addWidget(LCDNumbers);
    setLayout(layout);
}


void LCDNumberWidget::init()
{
    LCDNumbers->setDigitCount(10);
}

void LCDNumberWidget::paintWidget()
{
    LCDNumbers->display(data.at(0));
}
