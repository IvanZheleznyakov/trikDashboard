#pragma once
#include "telemetry_const.h"
#include "widgetbutton.h"
#include "expressioninputdialog.h"

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
    void requestDataToSubscribe(QString, QString);
    void requestDataToUnscribe(QString, QString);

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
    void connectButtons();
    void insertGroupOfWidgets(QVector<QString> &nameOfWidgets);
    void insertNewExpression();
    void widgetButtonIsPressed(QString widgetName, QString deviceName, bool isActive);
    void addExpressionButtonIsClicked();
    WidgetButton *createPlotButton(QString deviceName);
    WidgetButton *createLCDNumberButton(QString deviceName);
    WidgetButton *createProgressBarButton(QString deviceName);
    WidgetButton *createTableButton(QString deviceName);
    QPushButton *createExpressionsButton();

private:
    QLineEdit *mPortTextEdit;
    QLineEdit *mIpTextEdit;
    QLabel *mIpLabel;
    QLabel *mPortLabel;
    QPushButton *mConnectButton;
    ExpressionInputDialog *expressionInputDialog;
    QToolBox *mTelemetry;
    QVector<WidgetButton *> mWidgetButtons;
};
