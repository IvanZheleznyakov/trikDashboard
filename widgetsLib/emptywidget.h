#pragma once
#include "widgetslib_global.h"
#include "dashboardwidget.h"
#include <QWidget>

class WIDGETSLIBSHARED_EXPORT EmptyWidget : public DashboardWidget
{
    Q_OBJECT
public:
    EmptyWidget(QString title);

public slots:
    void paint();
    void init();
};
