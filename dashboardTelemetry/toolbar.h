#pragma once
#include "telemetry_const.h"
#include "widgetbutton.h"

#include <QToolBar>
#include <QLineEdit>
#include <QToolBox>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QVector>

class ToolBar : public QToolBar
{
    Q_OBJECT

public:
    ToolBar();
    QToolBox *menuBox;

signals:
    void setConnection(QString ip, int port);

protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

public slots:
    void insertTelemetry();
    void deleteTelemetry();

private slots:
    void retranslateUi();
    void insertToolBox();
    void connectButtonPressed();

private:
    QLineEdit *mPortTextEdit;
    QLineEdit *mIpTextEdit;
    QLabel *mIpLabel;
    QLabel *mPortLabel;
    QPushButton *mConnectButton;
    QToolBox *mTelemetry;
    QVector<WidgetButton *> mWidgetButtons;
};
