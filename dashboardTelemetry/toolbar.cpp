#include "toolbar.h"

#include <QMainWindow>
#include <QMenu>
#include <QComboBox>
#include <QBoxLayout>
#include <QGroupBox>
#include <stdlib.h>

//this
#include <QPushButton>

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
    ipLabel->setText(tr("Connect to IP:"));
    portLabel->setText(tr("Port:"));
    connectButton->setText(tr("Connect"));
    menuBox->setItemText(0, tr("Connection"));
    menuBox->setItemText(1, tr("Settings"));
    if (menuBox->count() > 2) {
        menuBox->setItemText(2, tr("Telemetry"));
        telemetry->setItemText(0, tr("3D sensors"));
        telemetry->setItemText(1, tr("Analog sensors"));
        telemetry->setItemText(2, tr("Servomotors"));
        telemetry->setItemText(3, tr("Motors"));
        telemetry->setItemText(4, tr("Encoders"));
        telemetry->setItemText(5, tr("Battery"));
        telemetry->setItemText(6, tr("Camera"));
        telemetry->setItemText(7, tr("Alerts"));
    }
}

void ToolBar::insertToolBox()
{
    menuBox->setStyleSheet("QToolBox::tab { background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #E1E1E1, stop: 0.4 #DDDDDD, stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3); border-radius: 3px; color: darkgray; }"
                       "QToolBox::tab:selected { font: italic; color: black;}");

    QGroupBox *connectToTRIK = new QGroupBox();
    QVBoxLayout *connectToTRIKLayout = new QVBoxLayout;
    ipLabel = new QLabel();
    ipTextEdit = new QLineEdit(START_IP_STRING);
    portLabel = new QLabel();
    portTextEdit = new QLineEdit(START_PORT_STRING);
    connectButton = new QPushButton();
    connectButton->setStyleSheet("QPushButton { background-color: rgb(170, 170, 170); border-style: outset; border-width: 0.5px; border-radius: 5px; border-color: beige; padding: 4px;}"
                                 "QPushButton:pressed { background-color: rgb(200, 200, 200); border-style: inset; }");
    ipTextEdit->setFixedHeight(IPTEXT_HEIGHT);
    portTextEdit->setFixedHeight(PORTTEXT_HEIGHT);
    connectToTRIKLayout->addWidget(ipLabel);
    connectToTRIKLayout->addWidget(ipTextEdit);
    connectToTRIKLayout->addWidget(portLabel);
    connectToTRIKLayout->addWidget(portTextEdit);
    connectToTRIKLayout->addWidget(connectButton);
    connectToTRIKLayout->addStretch(0);
    connectToTRIK->setLayout(connectToTRIKLayout);
    menuBox->addItem(connectToTRIK, "");

    connect(connectButton, &QPushButton::clicked, this, &ToolBar::connectButtonPressed);

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
    telemetry = new QToolBox();
    telemetry->setStyleSheet("QToolBox::tab { background: gray; border-radius: 3px; color: darkgray; }"
                             "QToolBox::tab:selected { font: italic; color: black;}");
    menuBox->addItem(telemetry, "");

    QGroupBox *sensors3D = new QGroupBox();
    QVBoxLayout *sensors3DLayout = new QVBoxLayout;

    QToolBox *test1t = new QToolBox();
    QGroupBox *test1 = new QGroupBox();
    QVBoxLayout *test1l = new QVBoxLayout;
    test1l->addWidget(new QPushButton("test1"));
    test1l->addWidget(new QPushButton("test1"));
    test1l->addWidget(new QPushButton("test1"));
    test1l->addWidget(new QPushButton("test1"));
    test1->setLayout(test1l);
    test1t->addItem(test1, "");
    test1t->setItemText(0, "Accelerometr");
    sensors3DLayout->addWidget(test1t);

    QGroupBox *test2 = new QGroupBox();
    QVBoxLayout *test2l = new QVBoxLayout;
    test2l->addWidget(new QPushButton("test2"));
    test2l->addWidget(new QPushButton("test2"));
    test2l->addWidget(new QPushButton("test2"));
    test2l->addWidget(new QPushButton("test2"));
    test2->setLayout(test2l);
    test1t->addItem(test2, "");
    test1t->setItemText(1, "Gyroscope");

 //   sensors3DLayout->addWidget(panel->accelerometer->button());
//    sensors3DLayout->addWidget(panel->gyroscope->button());
    sensors3DLayout->addStretch(0);
    sensors3D->setLayout(sensors3DLayout);
    telemetry->addItem(sensors3D, "");

    QGroupBox* analogSensors = new QGroupBox();
    QVBoxLayout* analogSensorsLayout = new QVBoxLayout;
    analogSensors->setLayout(analogSensorsLayout);
    telemetry->addItem(analogSensors, "");

    QGroupBox* servoMotors = new QGroupBox();
    QVBoxLayout* servoMotorsLayout = new QVBoxLayout;
    servoMotors->setLayout(servoMotorsLayout);
    telemetry->addItem(servoMotors, "");

    QGroupBox* powerMotors = new QGroupBox();
    QVBoxLayout* powerMotorsLayout = new QVBoxLayout;
//    powerMotorsLayout->addWidget(panel->powerMotor1->button());
//    powerMotorsLayout->addWidget(panel->powerMotor2->button());
//    powerMotorsLayout->addWidget(panel->powerMotor3->button());
//    powerMotorsLayout->addWidget(panel->powerMotor4->button());
    powerMotorsLayout->addStretch(0);
    powerMotors->setLayout(powerMotorsLayout);
    telemetry->addItem(powerMotors, "");

    QGroupBox* encoders = new QGroupBox();
    QVBoxLayout* encodersLayout = new QVBoxLayout;
    encoders->setLayout(encodersLayout);
    telemetry->addItem(encoders, "");


    QGroupBox* batteryGroup = new QGroupBox();
    QVBoxLayout* batteryLayout = new QVBoxLayout();
//    batteryLayout->addWidget(panel->battery->button());
    batteryLayout->addStretch(0);
    batteryGroup->setLayout(batteryLayout);
    telemetry->addItem(batteryGroup, "");

    QGroupBox *cameraGroup = new QGroupBox();
    QVBoxLayout *cameraLayout = new QVBoxLayout();
    cameraLayout->addStretch(0);
    cameraGroup->setLayout(cameraLayout);
    telemetry->addItem(cameraGroup, "");

    QGroupBox *alertsGroup = new QGroupBox();
    QVBoxLayout *alertsLayout = new QVBoxLayout();
//    foreach (Sensor *sensor, panel->sensors) {
//        alertsLayout->addWidget(sensor->alertButton());
//    }
    alertsLayout->addStretch(0);
    alertsGroup->setLayout(alertsLayout);
    telemetry->addItem(alertsGroup, "");

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
    int port = portTextEdit->text().trimmed().toInt();
    emit setConnection(ipTextEdit->text(), port);
}
