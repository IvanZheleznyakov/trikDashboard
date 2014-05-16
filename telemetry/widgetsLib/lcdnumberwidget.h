#pragma once
#include "widgetslib_global.h"
#include "dashboardwidget.h"
#include "qcustomplot.h"

#include <QLCDNumber>
class WIDGETSLIBSHARED_EXPORT LCDNumberWidget : public DashboardWidget
{
public:
    LCDNumberWidget(QString title);

public slots:
    void paintWidget();
    void init();

private:
    QCustomPlot* plot;
    QLCDNumber* LCDNumbers;

};
