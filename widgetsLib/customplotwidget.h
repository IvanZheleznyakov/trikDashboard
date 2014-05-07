#pragma once
#include "dashboardwidget.h"
#include "qcustomplot.h"

class CustomPlotWidget : public DashboardWidget
{
public:
    CustomPlotWidget(int axis, QString title);

public slots:
    void paint();
    void init();

private:
    void addGraph(int n, QColor color);
    QCustomPlot plot;
    QLabel* labelNumders;

};
