#include "progressbarwidget.h"
#include "math.h"

ProgressBarWidget::ProgressBarWidget(QString title, int timerInterval) :
    DashboardWidget(1, title, timerInterval)
{
    connect(paintTimer, &QTimer::timeout, this, &ProgressBarWidget::paintWidget);
    progressBar = new QProgressBar();

    init();

    layout->addWidget(progressBar);
    setLayout(layout);
}


void ProgressBarWidget::init()
{
//    this->setInterval(60);
    progressBar->setTextVisible(true);
    progressBar->setStyleSheet("QProgressBar { border: 2px solid grey; border-radius: 5px; text-align: center; } QProgressBar::chunk { background-color: #C0C0C0;width: 20px;}");
    progressBar->setOrientation(Qt::Horizontal);
    progressBar->setRange(0,100);
}

void ProgressBarWidget::paintWidget()
{
    progressBar->setValue(floor(data.at(0)));
}
