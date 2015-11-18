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
#include <progressbarwidget.h>
#include "dockwidget.h"

#include <QPair>
#include "tablewidget.h"
#include "alert.h"

class Alert;
class DockWidget;
class Sensor : public QObject
{
    Q_OBJECT

public:
    explicit Sensor(QString title, QString devName, QObject *parent = 0);
    bool active();
    void setTitle(QString newTitle);
    QString getTitle();
    QVector<DashboardWidget*> widgets();
    QPushButton* button();
    QPushButton *alertButton();
    void retranslateUi();

signals:
    void newData(QVector<float> newData);
    void command(QString command);
    void newDockWidget(QDockWidget* dockWidget);

public slots:
    void actionTriggered();
    void setActive();
    void setInactive();
    void createDashboardWidgets();

private:
    bool pActive;
    QPushButton* sensorButton;
    QString title;
    QString devName;
    QVector<DockWidget*> dockWidget;
//    QVector<DashboardWidget*> pWidgets;
    QPair<QVector<DockWidget*>, QVector<DashboardWidget*> > pWidgets;
    Alert *alert;

};
