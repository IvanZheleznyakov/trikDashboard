#pragma once
#include "telemetry_const.h"
#include "toolbar.h"
#include <QMainWindow>
#include <QDockWidget>
#include <QTranslator>

class ControlPanel : public QMainWindow
{
    Q_OBJECT
public:
    ControlPanel(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    QTranslator appTranslator;

    void changeEvent(QEvent *event);

signals:
    void newConnection();
    void lostConnection();
    void setConnection(QString ip, int port);

public slots:
    void setStatusBarText(const QString text);

protected:
    void showEvent(QShowEvent *event);

private slots:
    void retranslateUi();
    void createDockWidget(QDockWidget* dw);

private:
    ToolBar *mToolBar;
};
