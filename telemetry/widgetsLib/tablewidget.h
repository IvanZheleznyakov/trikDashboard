#pragma once
#include "widgetslib_global.h"
#include "dashboardwidget.h"
#include <QTableWidget>
#include <QDateTime>

class WIDGETSLIBSHARED_EXPORT TableWidget : public DashboardWidget
{
public:
    TableWidget(int axis, QString title);

public slots:
    void paintWidget();
    void init();

private:
    static const int pMaxOfRows;

    int pRowToWriteData;
    QTableWidget *pTable;
};
