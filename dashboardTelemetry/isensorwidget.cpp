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

QVector<QColor> ISensorWidget::getColors() const
{
    return colors;
}

void ISensorWidget::setColors(const QVector<QColor> &value)
{
    colors = value;
}

QVector<float> ISensorWidget::getData() const
{
    return data;
}

void ISensorWidget::setData(const QVector<float> &value)
{
    data = value;
}

QGridLayout *ISensorWidget::getLayout() const
{
    return layout;
}

void ISensorWidget::setLayout(QGridLayout *value)
{
    layout = value;
}

QLabel *ISensorWidget::getTitleLabel() const
{
    return titleLabel;
}

void ISensorWidget::setTitleLabel(QLabel *value)
{
    titleLabel = value;
}

QMenu *ISensorWidget::getWidgetMenu() const
{
    return widgetMenu;
}

void ISensorWidget::setWidgetMenu(QMenu *value)
{
    widgetMenu = value;
}

QTimer *ISensorWidget::getPaintTimer() const
{
    return paintTimer;
}

void ISensorWidget::setPaintTimer(QTimer *value)
{
    paintTimer = value;
}

QString ISensorWidget::getTitle() const
{
    return title;
}

void ISensorWidget::setTitle(const QString &value)
{
    title = value;
}

int ISensorWidget::getAxis() const
{
    return axis;
}

void ISensorWidget::setAxis(int value)
{
    axis = value;
}

int ISensorWidget::getTimerInterval() const
{
    return timerInterval;
}

void ISensorWidget::setTimerInterval(int value)
{
    timerInterval = value;
}
