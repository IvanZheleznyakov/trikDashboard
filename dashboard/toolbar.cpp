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
    insertTelemetry();

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
    QLabel* ipLabel = new QLabel("Connect to IP:");
    ipTextEdit = new QLineEdit(START_IP_STRING);
    QLabel* portLabel = new QLabel("Port:");
    portTextEdit = new QLineEdit(START_PORT_STRING);
    QPushButton* connectButton = new QPushButton("Connect");
    ipTextEdit->setFixedHeight(24);
    portTextEdit->setFixedHeight(24);
    connectToTRIKLayout->addWidget(ipLabel);
    connectToTRIKLayout->addWidget(ipTextEdit);
    connectToTRIKLayout->addWidget(portLabel);
    connectToTRIKLayout->addWidget(portTextEdit);
    connectToTRIKLayout->addWidget(connectButton);
    connectToTRIKLayout->addStretch(0);
    connectToTRIK->setLayout(connectToTRIKLayout);
    menuBox->addItem(connectToTRIK, "Connection");
    connect(connectButton,SIGNAL(clicked()),this,SLOT(connectButtonPressed()));

    this->addWidget(menuBox);

}

void ToolBar::insertTelemetry()
{
    QGroupBox *settings = new QGroupBox();
    QVBoxLayout *settingsLayout = new QVBoxLayout;
    QCheckBox* logging = new QCheckBox("Logging", this);
    settingsLayout->addWidget(logging);
    settingsLayout->addStretch(0);
    settings->setLayout(settingsLayout);
    menuBox->addItem(settings, "Settings");
    //----------------

    QToolBox* telemetry = new QToolBox();
    telemetry->setStyleSheet("QToolBox::tab { background: gray; border-radius: 3px; color: darkgray; }"
                             "QToolBox::tab:selected { font: italic; color: black;}");
    menuBox->addItem(telemetry, "Telemetry");

    QGroupBox* sensors3D = new QGroupBox();
    QVBoxLayout* sensors3DLayout = new QVBoxLayout;

    sensors3DLayout->addWidget(panel->accelerometer->button());
    sensors3DLayout->addWidget(panel->gyroscope->button());
    sensors3DLayout->addStretch(0);
    sensors3D->setLayout(sensors3DLayout);
    telemetry->addItem(sensors3D,"3D sensors");

    QGroupBox* analogSensors = new QGroupBox();
    QVBoxLayout* analogSensorsLayout = new QVBoxLayout;
    QPushButton* analog=new QPushButton("Sensor 1",this);
    analogSensorsLayout->addWidget(analog);
    analogSensorsLayout->addStretch(0);
    analogSensors->setLayout(analogSensorsLayout);
    telemetry->addItem(analogSensors,"Analog sensors");

    QGroupBox* servoMotors = new QGroupBox();
    QVBoxLayout* servoMotorsLayout = new QVBoxLayout;
    QPushButton* smotor1=new QPushButton("Servomotor 1",this);
    servoMotorsLayout->addWidget(smotor1);
    servoMotorsLayout->addStretch(0);
    servoMotors->setLayout(servoMotorsLayout);
    telemetry->addItem(servoMotors,"Servomotors");

    QGroupBox* powerMotors = new QGroupBox();
    QVBoxLayout* powerMotorsLayout = new QVBoxLayout;
    QPushButton* pmotor1=new QPushButton("Motor 1",this);
    powerMotorsLayout->addWidget(pmotor1);
    powerMotorsLayout->addStretch(0);
    powerMotors->setLayout(powerMotorsLayout);
    telemetry->addItem(powerMotors,"Motors");

    QGroupBox* encoders = new QGroupBox();
    QVBoxLayout* encodersLayout = new QVBoxLayout;
    QPushButton* encoder=new QPushButton("Encoder 1",this);
    encodersLayout->addWidget(encoder);
    encodersLayout->addStretch(0);
    encoders->setLayout(encodersLayout);
    telemetry->addItem(encoders,"Encoders");

    QMenu* battery=new QMenu();
    telemetry->addItem(battery,"Battery");

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
