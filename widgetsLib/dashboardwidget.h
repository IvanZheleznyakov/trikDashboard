#pragma once

#include "widgetslib_global.h"
#include <QVector>
#include <QTimer>
#include <QGridLayout>
#include <QMenu>
#include <QLabel>

class WIDGETSLIBSHARED_EXPORT DashboardWidget : public QWidget
{

public:
    explicit DashboardWidget(int axis, QString title, QWidget *parent = 0);

public slots:
    void updateData(QVector <double> updates);
    virtual void paint() = 0;
    virtual void init() = 0;
    void setInterval(int interval);

protected:
    QVector<QColor> colors;
    QVector<double> data;
    QGridLayout *layout;
    QLabel* titleLabel;
    QMenu* widgetMenu;
    QTimer paintTimer;
    QString title;
    int axis;
    int timerInterval;

};
