#pragma once

#include "widgetslib_global.h"
#include <QWidget>
#include <QVector>
#include <QTimer>
#include <QGridLayout>
#include <QMenu>
#include <QLabel>

class WIDGETSLIBSHARED_EXPORT DashboardWidget : public QWidget
{

public:
    explicit DashboardWidget(int axis, QString title, int timerInterval, QWidget *parent = 0);

public slots:
    void startPaint();
    void stopPaint();
    void updateData(QVector <float> updates);
    void setInterval(int interval);
    virtual void paintWidget() = 0;
    virtual void init() = 0;

protected:
    QVector<QColor> colors;
    QVector<float> data;
    QGridLayout *layout;
    QLabel* titleLabel;
    QMenu* widgetMenu;
    QTimer* paintTimer;
    QString title;
    int axis;
    int timerInterval;

};
