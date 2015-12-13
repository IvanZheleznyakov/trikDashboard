#include "isensorwidget.h"

ISensorWidget::ISensorWidget(int axis, QString title, int timerInterval, QWidget *parent) :
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
