#pragma once
#include "../telemetry_const.h"

#include <QObject>
#include <QAction>
#include <QDockWidget>
#include <QVector>
#include <QPushButton>
#include "dashboardwidget.h"
#include <customplotwidget.h>
#include <emptywidget.h>
#include <lcdnumberwidget.h>
#include "dockwidget.h"

class DockWidget;
class Sensor : public QObject
{
    Q_OBJECT

public:
    explicit Sensor(QString title, QString devName, QObject *parent = 0);
    bool active();
    DashboardWidget* widget();
    QPushButton* button();

signals:
    void newData(QVector<float> newData);
    void command(QString command);
    void newDockWidget(DockWidget* dockWidget);

public slots:
    void actionTriggered();
    void setActive();
    void setInactive();
    void createDashboardWidget();

private:
    bool pActive;
    QPushButton* sensorButton;
    QString title;
    QString devName;
    DockWidget* dockWidget;
    DashboardWidget* pWidget;

};
