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
        mTelemetry->setItemText(7, tr("Alerts"));
    }
}

void ToolBar::insertToolBox()
{
    menuBox->setStyleSheet("QToolBox::tab { background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #E1E1E1, stop: 0.4 #DDDDDD, stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3); border-radius: 3px; color: darkgray; }"
                       "QToolBox::tab:selected { font: italic; color: black;}");

    QGroupBox *connectToTRIK = new QGroupBox();
    QVBoxLayout *connectToTRIKLayout = new QVBoxLayout;
    mIpLabel = new QLabel();
    mIpTextEdit = new QLineEdit(START_IP_STRING);
    mPortLabel = new QLabel();
    mPortTextEdit = new QLineEdit(START_PORT_STRING);
    mConnectButton = new QPushButton();
    mConnectButton->setStyleSheet("QPushButton { background-color: rgb(170, 170, 170); border-style: outset; border-width: 0.5px; border-radius: 5px; border-color: beige; padding: 4px;}"
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
    mTelemetry->setStyleSheet("QToolBox::tab { background: gray; border-radius: 3px; color: darkgray; }"
                             "QToolBox::tab:selected { font: italic; color: black;}");
    menuBox->addItem(mTelemetry, "");

    QGroupBox *sensors3D = new QGroupBox();
    QVBoxLayout *sensors3DLayout = new QVBoxLayout;

    QToolBox *accelerometerToolBox = new QToolBox();
    QGroupBox *accelerometerGroupBox = new QGroupBox();
    QVBoxLayout *accelerometerLayout = new QVBoxLayout;
    WidgetButton *accelerometerPlotButton = new WidgetButton("Plot", TelemetryConst::ACCELEROMETER_TITLE());
    accelerometerLayout->addWidget(accelerometerPlotButton);
    mWidgetButtons.append(accelerometerPlotButton);
    WidgetButton *accelerometerTableButton = new WidgetButton("Table", TelemetryConst::ACCELEROMETER_TITLE());
    accelerometerLayout->addWidget(accelerometerTableButton);
    mWidgetButtons.append(accelerometerTableButton);
    accelerometerGroupBox->setLayout(accelerometerLayout);
    accelerometerToolBox->addItem(accelerometerGroupBox, "");
    accelerometerToolBox->setItemText(0, TelemetryConst::ACCELEROMETER_TITLE());
    sensors3DLayout->addWidget(accelerometerToolBox);

 //   sensors3DLayout->addWidget(panel->accelerometer->button());
//    sensors3DLayout->addWidget(panel->gyroscope->button());
    sensors3DLayout->addStretch(0);
    sensors3D->setLayout(sensors3DLayout);
    mTelemetry->addItem(sensors3D, "");

    QGroupBox* analogSensors = new QGroupBox();
    QVBoxLayout* analogSensorsLayout = new QVBoxLayout;
    analogSensors->setLayout(analogSensorsLayout);
    mTelemetry->addItem(analogSensors, "");

    QGroupBox* servoMotors = new QGroupBox();
    QVBoxLayout* servoMotorsLayout = new QVBoxLayout;
    servoMotors->setLayout(servoMotorsLayout);
    mTelemetry->addItem(servoMotors, "");

    QGroupBox* powerMotors = new QGroupBox();
    QVBoxLayout* powerMotorsLayout = new QVBoxLayout;
//    powerMotorsLayout->addWidget(panel->powerMotor1->button());
//    powerMotorsLayout->addWidget(panel->powerMotor2->button());
//    powerMotorsLayout->addWidget(panel->powerMotor3->button());
//    powerMotorsLayout->addWidget(panel->powerMotor4->button());
    powerMotorsLayout->addStretch(0);
    powerMotors->setLayout(powerMotorsLayout);
    mTelemetry->addItem(powerMotors, "");

    QGroupBox* encoders = new QGroupBox();
    QVBoxLayout* encodersLayout = new QVBoxLayout;
    encoders->setLayout(encodersLayout);
    mTelemetry->addItem(encoders, "");


    QGroupBox* batteryGroup = new QGroupBox();
    QVBoxLayout* batteryLayout = new QVBoxLayout();
//    batteryLayout->addWidget(panel->battery->button());
    batteryLayout->addStretch(0);
    batteryGroup->setLayout(batteryLayout);
    mTelemetry->addItem(batteryGroup, "");

    QGroupBox *cameraGroup = new QGroupBox();
    QVBoxLayout *cameraLayout = new QVBoxLayout();
    cameraLayout->addStretch(0);
    cameraGroup->setLayout(cameraLayout);
    mTelemetry->addItem(cameraGroup, "");

    QGroupBox *alertsGroup = new QGroupBox();
    QVBoxLayout *alertsLayout = new QVBoxLayout();
//    foreach (Sensor *sensor, panel->sensors) {
//        alertsLayout->addWidget(sensor->alertButton());
//    }
    alertsLayout->addStretch(0);
    alertsGroup->setLayout(alertsLayout);
    mTelemetry->addItem(alertsGroup, "");

    retranslateUi();
}

void ToolBar::deleteTelemetry()
{
    menuBox->deleteLater();

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
