#include "toolbar.h"

#include <QMainWindow>
#include <QMenu>
#include <QLabel>
#include <QToolBox>
#include <QCheckBox>
#include <QPushButton>
#include <QBoxLayout>
#include <QGroupBox>
#include <stdlib.h>

ToolBar::ToolBar(ControlPanel* panel)
    : QToolBar(),
      panel(panel)
{

    //setWindowTitle(title);
    //setObjectName(title);
    //setIconSize(QSize(32, 32));
    menuBox = new QToolBox();
    insertToolBox();

    setMovable(false);
    this->setFixedWidth(TOOLBAR_WIDTH);

}

void ToolBar::insertToolBox()
{
    menuBox->setStyleSheet("QToolBox::tab { background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #E1E1E1, stop: 0.4 #DDDDDD, stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3); border-radius: 3px; color: darkgray; }"
                       "QToolBox::tab:selected { font: italic; color: black;}");

    //----------------
    QGroupBox *connectToTRIK = new QGroupBox();
    QVBoxLayout *connectToTRIKLayout = new QVBoxLayout;
    QLabel* ipLabel = new QLabel(tr("Connect to IP:"));
    ipTextEdit = new QLineEdit(START_IP_STRING);
    QLabel* portLabel = new QLabel(tr("Port:"));
    portTextEdit = new QLineEdit(START_PORT_STRING);
    QPushButton* connectButton = new QPushButton(tr("Connect"));
    connectButton->setStyleSheet("QPushButton { background-color: rgb(170, 170, 170); border-style: outset; border-width: 0.5px; border-radius: 5px; border-color: beige; padding: 4px;}"
                                 "QPushButton:pressed { background-color: rgb(200, 200, 200); border-style: inset; }");
    ipTextEdit->setFixedHeight(24);
    portTextEdit->setFixedHeight(24);
    connectToTRIKLayout->addWidget(ipLabel);
    connectToTRIKLayout->addWidget(ipTextEdit);
    connectToTRIKLayout->addWidget(portLabel);
    connectToTRIKLayout->addWidget(portTextEdit);
    connectToTRIKLayout->addWidget(connectButton);
    connectToTRIKLayout->addStretch(0);
    connectToTRIK->setLayout(connectToTRIKLayout);
    menuBox->addItem(connectToTRIK, tr("Connection"));
    connect(connectButton,SIGNAL(clicked()),this,SLOT(connectButtonPressed()));

    this->addWidget(menuBox);
    insertTelemetry();
}

void ToolBar::insertTelemetry()
{
    QGroupBox *settings = new QGroupBox();
    QVBoxLayout *settingsLayout = new QVBoxLayout;
    QCheckBox* logging = new QCheckBox(tr("Logging"), this);
    settingsLayout->addWidget(logging);
    settingsLayout->addStretch(0);
    settings->setLayout(settingsLayout);
    menuBox->addItem(settings, tr("Settings"));
    //----------------

    QToolBox* telemetry = new QToolBox();
    telemetry->setStyleSheet("QToolBox::tab { background: gray; border-radius: 3px; color: darkgray; }"
                             "QToolBox::tab:selected { font: italic; color: black;}");
    menuBox->addItem(telemetry, tr("Telemetry"));

    QGroupBox* sensors3D = new QGroupBox();
    QVBoxLayout* sensors3DLayout = new QVBoxLayout;

    sensors3DLayout->addWidget(panel->accelerometer->button());
    sensors3DLayout->addWidget(panel->gyroscope->button());
    sensors3DLayout->addStretch(0);
    sensors3D->setLayout(sensors3DLayout);
    telemetry->addItem(sensors3D,tr("3D sensors"));

    QGroupBox* analogSensors = new QGroupBox();
    QVBoxLayout* analogSensorsLayout = new QVBoxLayout;
    //QPushButton* analog=new QPushButton("Sensor 1",this);
    //analogSensorsLayout->addWidget(analog);
    //analogSensorsLayout->addStretch(0);
    analogSensors->setLayout(analogSensorsLayout);
    telemetry->addItem(analogSensors,tr("Analog sensors"));

    QGroupBox* servoMotors = new QGroupBox();
    QVBoxLayout* servoMotorsLayout = new QVBoxLayout;
    //QPushButton* smotor1=new QPushButton("Servomotor 1",this);
    //servoMotorsLayout->addWidget(smotor1);
    //servoMotorsLayout->addStretch(0);
    servoMotors->setLayout(servoMotorsLayout);
    telemetry->addItem(servoMotors,tr("Servomotors"));

    QGroupBox* powerMotors = new QGroupBox();
    QVBoxLayout* powerMotorsLayout = new QVBoxLayout;
    powerMotorsLayout->addWidget(panel->powerMotor1->button());
    powerMotorsLayout->addWidget(panel->powerMotor2->button());
    powerMotorsLayout->addWidget(panel->powerMotor3->button());
    powerMotorsLayout->addWidget(panel->powerMotor4->button());
    powerMotorsLayout->addStretch(0);
    powerMotors->setLayout(powerMotorsLayout);
    telemetry->addItem(powerMotors,tr("Motors"));

    QGroupBox* encoders = new QGroupBox();
    QVBoxLayout* encodersLayout = new QVBoxLayout;
    //QPushButton* encoder=new QPushButton("Encoder 1",this);
    //encodersLayout->addWidget(encoder);
    //encodersLayout->addStretch(0);
    encoders->setLayout(encodersLayout);
    telemetry->addItem(encoders,tr("Encoders"));


    QGroupBox* batteryGroup = new QGroupBox();
    QVBoxLayout* batteryLayout = new QVBoxLayout();
    batteryLayout->addWidget(panel->battery->button());
    batteryLayout->addStretch(0);
    batteryGroup->setLayout(batteryLayout);
    telemetry->addItem(batteryGroup,tr("Battery"));


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
