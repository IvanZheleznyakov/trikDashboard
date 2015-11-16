#pragma once
#include "widgetslib_global.h"
#include "dashboardwidget.h"

#include <QLCDNumber>
class WIDGETSLIBSHARED_EXPORT LCDNumberWidget : public DashboardWidget
{
public:
    LCDNumberWidget(QString title, int timerInterval);

public slots:
    void paintWidget();
    void init();

private:
    QLCDNumber* LCDNumbers;

};
