#pragma once
#include "widgetslib_global.h"
#include "dashboardwidget.h"
#include "qcustomplot.h"

class WIDGETSLIBSHARED_EXPORT CustomPlotWidget : public DashboardWidget
{
public:
    CustomPlotWidget(int axis, QString title, int timerInterval);

public slots:
    void paintWidget();
    void init();

private slots:
    void addGraph(int n, QColor color);

private:
    QCustomPlot* plot;
    QLabel* labelNumders;

};
