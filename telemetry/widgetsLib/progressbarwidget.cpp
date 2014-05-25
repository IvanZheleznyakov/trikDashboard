#include "progressbarwidget.h"
#include "math.h"

ProgressBarWidget::ProgressBarWidget(QString title) :
    DashboardWidget(1, title)
{
    connect(paintTimer, &QTimer::timeout, this, &ProgressBarWidget::paintWidget);
    progressBar = new QProgressBar();

    init();

    layout->addWidget(progressBar);
    setLayout(layout);
}


void ProgressBarWidget::init()
{
    this->setInterval(20);
    progressBar->setTextVisible(true);
    progressBar->setStyleSheet("QProgressBar { border: 2px solid grey; border-radius: 5px; text-align: center; } QProgressBar::chunk { background-color: #05B8CC;width: 20px;}");
    progressBar->setOrientation(Qt::Horizontal);
    progressBar->setRange(0,100);
}

void ProgressBarWidget::paintWidget()
{
    progressBar->setValue(floor(data.at(0)));
}
