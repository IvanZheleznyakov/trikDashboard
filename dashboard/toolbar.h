#pragma once

#include <QToolBar>
#include <QLineEdit>

QT_FORWARD_DECLARE_CLASS(QAction)
QT_FORWARD_DECLARE_CLASS(QToolBox)

class ToolBar : public QToolBar
{
    Q_OBJECT

public:
    ToolBar(const QString &title, QWidget *parent);
    QToolBox* menuBox;
    QAction* accelAction;
    QAction* gyroAction;

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

};
