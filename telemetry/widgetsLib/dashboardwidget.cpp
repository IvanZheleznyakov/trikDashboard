#include "dashboardwidget.h"

DashboardWidget::DashboardWidget(int axis, QString title, int timerInterval, QWidget *parent) :
    QWidget(parent),
    data(axis),
    title(title),
    axis(axis),
    timerInterval(timerInterval)
{
    this->setStyleSheet("background-color: white");
    data.fill(0.0);
    colors << QColor("red") << QColor("blue") << QColor("green");
    paintTimer = new QTimer(this);
    layout = new QGridLayout;
    titleLabel = new QLabel(title);
    titleLabel->setAlignment(Qt::AlignCenter);

    paintTimer->setInterval(timerInterval);
}

void DashboardWidget::startPaint()
{
    paintTimer->start(timerInterval);
}

void DashboardWidget::stopPaint()
{
    paintTimer->stop();
}

void DashboardWidget::setInterval(int interval)
{
    timerInterval = interval;
}

void DashboardWidget::updateData(QVector<float> updates)
{
    int n = updates.size();
    n = n >= axis ? axis : n;
    for (int i = 0; i < n; i++)
    {
        data[i] = updates.at(i);
    }
}
