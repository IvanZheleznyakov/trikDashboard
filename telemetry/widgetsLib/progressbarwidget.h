#pragma once
#include "widgetslib_global.h"
#include "dashboardwidget.h"
#include <QProgressBar>
#include <QLabel>

class WIDGETSLIBSHARED_EXPORT ProgressBarWidget : public DashboardWidget
{
public:
    ProgressBarWidget(QString title, int timerInterval);

public slots:
    void paintWidget();
    void init();

private:
    QProgressBar* progressBar;
    QLabel* labelNumders;

};
