#include "lcdnumberwidget.h"

LCDNumberWidget::LCDNumberWidget(QString title) :
    DashboardWidget(1, title)
{
    connect(paintTimer, &QTimer::timeout, this, &LCDNumberWidget::paintWidget);
    LCDNumbers = new QLCDNumber();

    init();

    layout->addWidget(LCDNumbers);
    setLayout(layout);
}


void LCDNumberWidget::init()
{
    this->setInterval(1000);

    LCDNumbers->setDigitCount(10);
}

void LCDNumberWidget::paintWidget()
{
    LCDNumbers->display(data.at(0));
}
