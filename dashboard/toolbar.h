#pragma once

#include <QToolBar>
#include <QLineEdit>
#include <controlpanel.h>

QT_FORWARD_DECLARE_CLASS(QAction)
QT_FORWARD_DECLARE_CLASS(QToolBox)

class ToolBar : public QToolBar
{
    Q_OBJECT

public:
    ToolBar(const QString &title, ControlPanel* panel);
    QToolBox* menuBox;
    QAction* accelAction;
    QAction* gyroAction;
    void insertTelemetry();

signals:
    void setConnection(QString ip, int port);

protected:
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);

private slots:
    void connectButtonPressed();

private:
    void insertToolBox();
    QLineEdit* portTextEdit;
    QLineEdit* ipTextEdit;
    ControlPanel* panel;

};
