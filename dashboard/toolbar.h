#pragma once
#include "dashboard_const.h"

#include <QToolBar>
#include <QLineEdit>
#include <QToolBox>
#include <controlpanel.h>

class ToolBar : public QToolBar
{
    Q_OBJECT

public:
    ToolBar(ControlPanel* panel);
    QToolBox* menuBox;

signals:
    void setConnection(QString ip, int port);

protected:
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);

public slots:
    void insertTelemetry();
    void deleteTelemetry();

private slots:
    void connectButtonPressed();

private:
    void insertToolBox();
    QLineEdit* portTextEdit;
    QLineEdit* ipTextEdit;
    ControlPanel* panel;

};
