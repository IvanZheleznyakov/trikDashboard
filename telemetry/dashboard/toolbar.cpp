#include "toolbar.h"

#include <QMainWindow>
#include <QMenu>
#include <QComboBox>
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
    setMovable(false);
    this->setFixedWidth(TOOLBAR_WIDTH);

    insertToolBox();
    //insertTelemetry();

    retranslateUi();
}

void ToolBar::retranslateUi()
{
    ipLabel->setText(tr("Connect to IP:"));
    portLabel->setText(tr("Port:"));
    connectButton->setText(tr("Connect"));
    menuBox->setItemText(0, tr("Connection"));
    menuBox->setItemText(1, tr("Settings"));
    logging->setText(tr("Logging"));
    if (menuBox->count() > 2)
    {
        menuBox->setItemText(2, tr("Telemetry"));
        telemetry->setItemText(0, tr("3D sensors"));
        telemetry->setItemText(1, tr("Analog sensors"));
        telemetry->setItemText(2, tr("Servomotors"));
        telemetry->setItemText(3, tr("Motors"));
        telemetry->setItemText(4, tr("Encoders"));
        telemetry->setItemText(5, tr("Battery"));
        telemetry->setItemText(6, tr("Alerts"));
    }
}

void ToolBar::insertToolBox()
{
    menuBox->setStyleSheet("QToolBox::tab { background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #E1E1E1, stop: 0.4 #DDDDDD, stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3); border-radius: 3px; color: darkgray; }"
                       "QToolBox::tab:selected { font: italic; color: black;}");

    //----------------
    QGroupBox *connectToTRIK = new QGroupBox();
    QVBoxLayout *connectToTRIKLayout = new QVBoxLayout;
    ipLabel = new QLabel();
    ipTextEdit = new QLineEdit(START_IP_STRING);
    portLabel = new QLabel();
    portTextEdit = new QLineEdit(START_PORT_STRING);
    connectButton = new QPushButton();
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
    menuBox->addItem(connectToTRIK, "");

    connect(connectButton,SIGNAL(clicked()),this,SLOT(connectButtonPressed()));

    //----------------
    QGroupBox *settings = new QGroupBox();
    QVBoxLayout *settingsLayout = new QVBoxLayout;
    logging = new QCheckBox(this);
    QComboBox* box = new QComboBox();
    box->clear();
    box->insertItems(0, QStringList()
                     << tr("English", 0)
                     << tr("\320\240\321\203\321\201\321\201\320\272\320\270\320\271", 0)
                     );
    connect(box,SIGNAL(currentIndexChanged(int)),this,SLOT(setLanguage(int)));

    settingsLayout->addWidget(logging);
    settingsLayout->addWidget(box);
    settingsLayout->addStretch(0);
    settings->setLayout(settingsLayout);
    menuBox->addItem(settings, "");
    //----------------

    this->addWidget(menuBox);
}

void ToolBar::setLanguage(int lang)
{
    if (lang == 0)
    {
        panel->appTranslator.load("dashboard_eng");
    } else if (lang == 1)
    {
        panel->appTranslator.load("dashboard_ru");
    }
    retranslateUi();
}

void ToolBar::insertTelemetry()
{
    telemetry = new QToolBox();
    telemetry->setStyleSheet("QToolBox::tab { background: gray; border-radius: 3px; color: darkgray; }"
                             "QToolBox::tab:selected { font: italic; color: black;}");
    menuBox->addItem(telemetry, "");

    QGroupBox* sensors3D = new QGroupBox();
    QVBoxLayout* sensors3DLayout = new QVBoxLayout;

    sensors3DLayout->addWidget(panel->accelerometer->button());
    sensors3DLayout->addWidget(panel->gyroscope->button());
    sensors3DLayout->addStretch(0);
    sensors3D->setLayout(sensors3DLayout);
    telemetry->addItem(sensors3D,"");

    QGroupBox* analogSensors = new QGroupBox();
    QVBoxLayout* analogSensorsLayout = new QVBoxLayout;
    //QPushButton* analog=new QPushButton("Sensor 1",this);
    //analogSensorsLayout->addWidget(analog);
    //analogSensorsLayout->addStretch(0);
    analogSensors->setLayout(analogSensorsLayout);
    telemetry->addItem(analogSensors,"");

    QGroupBox* servoMotors = new QGroupBox();
    QVBoxLayout* servoMotorsLayout = new QVBoxLayout;
    //QPushButton* smotor1=new QPushButton("Servomotor 1",this);
    //servoMotorsLayout->addWidget(smotor1);
    //servoMotorsLayout->addStretch(0);
    servoMotors->setLayout(servoMotorsLayout);
    telemetry->addItem(servoMotors,"");

    QGroupBox* powerMotors = new QGroupBox();
    QVBoxLayout* powerMotorsLayout = new QVBoxLayout;
    powerMotorsLayout->addWidget(panel->powerMotor1->button());
    powerMotorsLayout->addWidget(panel->powerMotor2->button());
    powerMotorsLayout->addWidget(panel->powerMotor3->button());
    powerMotorsLayout->addWidget(panel->powerMotor4->button());
    powerMotorsLayout->addStretch(0);
    powerMotors->setLayout(powerMotorsLayout);
    telemetry->addItem(powerMotors,"");

    QGroupBox* encoders = new QGroupBox();
    QVBoxLayout* encodersLayout = new QVBoxLayout;
    //QPushButton* encoder=new QPushButton("Encoder 1",this);
    //encodersLayout->addWidget(encoder);
    //encodersLayout->addStretch(0);
    encoders->setLayout(encodersLayout);
    telemetry->addItem(encoders,"");


    QGroupBox* batteryGroup = new QGroupBox();
    QVBoxLayout* batteryLayout = new QVBoxLayout();
    batteryLayout->addWidget(panel->battery->button());
    batteryLayout->addStretch(0);
    batteryGroup->setLayout(batteryLayout);
    telemetry->addItem(batteryGroup,"");

    QGroupBox *alertsGroup = new QGroupBox();
    QVBoxLayout *alertsLayout = new QVBoxLayout();
    foreach (Sensor *sensor, panel->sensors) {
        alertsLayout->addWidget(sensor->alertButton());
    }

    alertsLayout->addStretch(0);
    alertsGroup->setLayout(alertsLayout);
    telemetry->addItem(alertsGroup,"");

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
