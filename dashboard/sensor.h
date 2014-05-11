#pragma once
#include <QObject>
#include <QAction>
#include <QDockWidget>
#include <QVector>
#include <QPushButton>
#include <dashboardwidget.h>
#include <customplotwidget.h>
#include <emptywidget.h>

class Sensor : public QObject
{
    Q_OBJECT

public:
    explicit Sensor(QString name, QObject *parent = 0);
    bool active();
    DashboardWidget* widget();
    QPushButton* button();

signals:
    void newData(QVector<float> newData);
    void command(QString command);
    void newDockWidget(QDockWidget* dockWidget);

private slots:
    void actionTriggered();
    void setActive();
    void setInactive();
    void createDashboardWidget();

private:
    bool pActive;
    QPushButton* sensorButton;
    QString name;
    QDockWidget* dockWidget;
    DashboardWidget* pWidget;

};
