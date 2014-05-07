#pragma once

#include <QMainWindow>
#include <QDockWidget>

class ToolBar;
class ControlPanel : public QMainWindow
{
    Q_OBJECT
public:
    ControlPanel(QWidget *parent = 0, Qt::WindowFlags flags = 0);

signals:
    void setConnection(QString ip, int port);

public slots:
    void setStatusBarText(const QString text);

protected:
    void showEvent(QShowEvent *event);

public slots:
    void createDockWidget();
    void destroyDockWidget();

private:
    ToolBar *toolBar;
    QList<QDockWidget*> widgets;

};
