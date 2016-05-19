#include "toolbar.h"

#include <QMainWindow>
#include <QMenu>
#include <QComboBox>
#include <QBoxLayout>
#include <QGroupBox>
#include <stdlib.h>

ToolBar::ToolBar()
    : QToolBar()
{
    menuBox = new QToolBox();
    setMovable(false);
    this->setFixedWidth(TOOLBAR_WIDTH);
    expressionInputDialog = new ExpressionInputDialog();
    connect(expressionInputDialog, ExpressionInputDialog::sendDataToExpression, this, ToolBar::insertNewExpression);

    insertToolBox();

    retranslateUi();
}

void ToolBar::retranslateUi()
{
    mIpLabel->setText(tr("Connect to IP:"));
    mPortLabel->setText(tr("Port:"));
    mConnectButton->setText(tr("Connect"));
    menuBox->setItemText(0, tr("Connection"));
    menuBox->setItemText(1, tr("Settings"));
    if (menuBox->count() > 2) {
        menuBox->setItemText(2, tr("Telemetry"));
        mTelemetry->setItemText(0, tr("3D sensors"));
        mTelemetry->setItemText(1, tr("Analog sensors"));
        mTelemetry->setItemText(2, tr("Servomotors"));
        mTelemetry->setItemText(3, tr("Motors"));
        mTelemetry->setItemText(4, tr("Encoders"));
        mTelemetry->setItemText(5, tr("Battery"));
        mTelemetry->setItemText(6, tr("Camera"));
        mTelemetry->setItemText(7, tr("Expressions"));
\
    }
}

void ToolBar::insertToolBox()
{
    menuBox->setStyleSheet("QToolBox::tab { background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #201f58, stop: 0.4 #201f54, stop: 0.5 #1e1d4d, stop: 1.0 #1b1a46); padding-left: 5px; border-radius: 9px; color: white; }"
                       "QToolBox::tab:selected { font: italic; color: white;}");

    QGroupBox *connectToTRIK = new QGroupBox();
    QVBoxLayout *connectToTRIKLayout = new QVBoxLayout;
    mIpLabel = new QLabel();
    mIpTextEdit = new QLineEdit(START_IP_STRING);
    mPortLabel = new QLabel();
    mPortTextEdit = new QLineEdit(START_PORT_STRING);
    mConnectButton = new QPushButton();
    mConnectButton->setStyleSheet("QPushButton { background-color: #74afb0; border-style: outset; border-width: 0.5px; border-radius: 5px; border-color: beige; padding: 4px; color: white;}"
                                 "QPushButton:pressed { background-color: rgb(200, 200, 200); border-style: inset; }");
    mIpTextEdit->setFixedHeight(IPTEXT_HEIGHT);
    mPortTextEdit->setFixedHeight(PORTTEXT_HEIGHT);
    connectToTRIKLayout->addWidget(mIpLabel);
    connectToTRIKLayout->addWidget(mIpTextEdit);
    connectToTRIKLayout->addWidget(mPortLabel);
    connectToTRIKLayout->addWidget(mPortTextEdit);
    connectToTRIKLayout->addWidget(mConnectButton);
    connectToTRIKLayout->addStretch(0);
    connectToTRIK->setLayout(connectToTRIKLayout);
    menuBox->addItem(connectToTRIK, "");

    connect(mConnectButton, &QPushButton::clicked, this, &ToolBar::connectButtonPressed);

    QGroupBox *settings = new QGroupBox();
    QVBoxLayout *settingsLayout = new QVBoxLayout;
    QComboBox *box = new QComboBox();
    box->clear();

    settingsLayout->addWidget(box);
    settingsLayout->addStretch(0);
    settings->setLayout(settingsLayout);
    menuBox->addItem(settings, "");

    this->addWidget(menuBox);
}

void ToolBar::insertTelemetry()
{
    mTelemetry = new QToolBox();
    mTelemetry->setStyleSheet("QToolBox::tab { background: #254871; border-radius: 9px; color: white; }"
                             "QToolBox::tab:selected { background: #4f89a3; font: italic; color: white;}");
    menuBox->addItem(mTelemetry, "");

    QVector<QString> nameOfSensors;

    //3D sensors
    nameOfSensors.append(TelemetryConst::ACCELEROMETER_TITLE());
    nameOfSensors.append(TelemetryConst::GYROSCOPE_TITLE());
    insertGroupOfWidgets(nameOfSensors);

    //analog sensors
    insertGroupOfWidgets(nameOfSensors);

    //servomotors
    insertGroupOfWidgets(nameOfSensors);

    //power motors
    nameOfSensors.append(TelemetryConst::POWER_MOTOR1_TITLE());
    nameOfSensors.append(TelemetryConst::POWER_MOTOR2_TITLE());
    nameOfSensors.append(TelemetryConst::POWER_MOTOR3_TITLE());
    nameOfSensors.append(TelemetryConst::POWER_MOTOR4_TITLE());
    insertGroupOfWidgets(nameOfSensors);

    //encoders
    insertGroupOfWidgets(nameOfSensors);

    //batteryGroup
    nameOfSensors.append(TelemetryConst::BATTERY_TITLE());
    insertGroupOfWidgets(nameOfSensors);

    //camera
    insertGroupOfWidgets(nameOfSensors);

    //expressions
    nameOfSensors.append("Expressions");
    insertGroupOfWidgets(nameOfSensors);

    connectButtons();
    retranslateUi();
}

void ToolBar::insertGroupOfWidgets(QVector<QString> &nameOfSensors)
{
    QGroupBox *groupBox = new QGroupBox();
    QVBoxLayout *vBoxLayout = new QVBoxLayout;
    QToolBox *groupToolBox = new QToolBox();

    if (nameOfSensors.count() != 0 && nameOfSensors.at(0) == "Expressions")
    {
        vBoxLayout->addWidget(createExpressionsButton());
        vBoxLayout->addStretch(0);
        groupBox->setLayout(vBoxLayout);
        mTelemetry->addItem(groupBox, "");
        nameOfSensors.clear();
    } else {
        for (int i = 0; i != nameOfSensors.count(); ++i) {
            QGroupBox *widgetGroupBox = new QGroupBox();
            QVBoxLayout *widgetLayout = new QVBoxLayout;
            if (nameOfSensors.at(i) == TelemetryConst::ACCELEROMETER_TITLE() ||
                nameOfSensors.at(i) == TelemetryConst::GYROSCOPE_TITLE()) {
                widgetLayout->addWidget(createPlotButton(nameOfSensors.at(i)));
            } else if (nameOfSensors.at(i) == TelemetryConst::BATTERY_TITLE()) {
                widgetLayout->addWidget(createLCDNumberButton(nameOfSensors.at(i)));
            } else if (nameOfSensors.at(i) == TelemetryConst::POWER_MOTOR1_TITLE() ||
                       nameOfSensors.at(i) == TelemetryConst::POWER_MOTOR2_TITLE() ||
                       nameOfSensors.at(i) == TelemetryConst::POWER_MOTOR3_TITLE() ||
                       nameOfSensors.at(i) == TelemetryConst::POWER_MOTOR4_TITLE()) {
                widgetLayout->addWidget(createProgressBarButton(nameOfSensors.at(i)));
            }

            widgetLayout->addWidget(createTableButton(nameOfSensors.at(i)));
            widgetGroupBox->setLayout(widgetLayout);
            groupToolBox->addItem(widgetGroupBox, "");
            groupToolBox->setItemText(i, nameOfSensors.at(i));
            vBoxLayout->addWidget(groupToolBox);
        }

        vBoxLayout->addStretch(0);
        groupBox->setLayout(vBoxLayout);
        mTelemetry->addItem(groupBox, "");
        nameOfSensors.clear();
    }
}

void ToolBar::insertNewExpression(QString name, QString expression)
{
    QToolBox *groupToolBox = new QToolBox();
    QGroupBox *widgetGroupBox = new QGroupBox();
    QVBoxLayout *widgetLayout = new QVBoxLayout;
    WidgetButton *expressionWidgetButton = createLCDNumberButton(name);
    connect(expressionWidgetButton, &WidgetButton::sendDataFromButton,
            this, &ToolBar::widgetButtonIsPressed);
    widgetLayout->addWidget(expressionWidgetButton);
//    widgetLayout->addWidget(createTableButton(deviceName));
    widgetGroupBox->setLayout(widgetLayout);
    groupToolBox->addItem(widgetGroupBox, "");
    groupToolBox->setItemText(0, name);
    mTelemetry->widget(7)->layout()->addWidget(groupToolBox);
    emit expressionIsCreated(name, expression);
}

WidgetButton *ToolBar::createPlotButton(QString deviceName)
{
    WidgetButton *plotButton = new WidgetButton(TelemetryConst::PLOT_TITLE(), deviceName);
    mWidgetButtons.append(plotButton);
    return plotButton;
}

WidgetButton *ToolBar::createLCDNumberButton(QString deviceName)
{
    WidgetButton *lcdNumberButton = new WidgetButton(TelemetryConst::LCDNUMBER_TITLE(), deviceName);
    mWidgetButtons.append(lcdNumberButton);
    return lcdNumberButton;
}

WidgetButton *ToolBar::createProgressBarButton(QString deviceName)
{
    WidgetButton *progressBarButton = new WidgetButton(TelemetryConst::PROGRESSBAR_TITLE(), deviceName);
    mWidgetButtons.append(progressBarButton);
    return progressBarButton;
}

WidgetButton *ToolBar::createTableButton(QString deviceName)
{
    WidgetButton *tableButton = new WidgetButton(TelemetryConst::TABLE_TITLE(), deviceName);
    mWidgetButtons.append(tableButton);
    return tableButton;
}

QPushButton *ToolBar::createExpressionsButton()
{
    QPushButton *expressionsButton = new QPushButton();
    expressionsButton->setText("Add new expression");
    expressionsButton->setStyleSheet("QPushButton { background-color: #74afb0; border-style: outset; border-width: 0.5px; border-radius: 5px; border-color: beige; padding: 4px; color: white;}"
                                     "QPushButton:pressed { background-color: rgb(200, 200, 200); border-style: inset; }");
    connect(expressionsButton, QPushButton::clicked, this, ToolBar::addExpressionButtonIsClicked);
    return expressionsButton;
}

void ToolBar::connectButtons()
{
    for (int i = 0; i != mWidgetButtons.count(); ++i) {
        connect(mWidgetButtons.at(i), &WidgetButton::sendDataFromButton,
                this, &ToolBar::widgetButtonIsPressed);
    }
}

void ToolBar::deleteTelemetry()
{
    menuBox->deleteLater();

    int numOfWidgets = mWidgetButtons.count();
    for (int i = 0; i != numOfWidgets; ++i) {
        delete mWidgetButtons.at(i);
    }

    mWidgetButtons.clear();

    menuBox = new QToolBox();
    insertToolBox();
}

void ToolBar::enterEvent(QEvent*)
{
}

void ToolBar::leaveEvent(QEvent*)
{
}

void ToolBar::connectButtonPressed()
{
    int port = mPortTextEdit->text().trimmed().toInt();
    emit setConnection(mIpTextEdit->text(), port);
}

void ToolBar::addExpressionButtonIsClicked()
{
    expressionInputDialog->show();
}

void ToolBar::widgetButtonIsPressed(QString widgetName, QString deviceName, bool isActive)
{
    if (isActive) {
        emit requestDataToSubscribe(widgetName, deviceName);
    } else {
        emit requestDataToUnscribe(widgetName, deviceName);
    }
}
