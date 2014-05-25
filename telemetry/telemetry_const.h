#pragma once
#include <QString>
#include <QKeySequence>
#include <QSize>

//dashboard names
QString const ACCELEROMETER_TITLE = "Accelerometer";
QString const GYROSCOPE_TITLE = "Gyroscope";
QString const BATTERY_TITLE = "Battery";
QString const POWER_MOTOR1_TITLE = "Motor 1";
QString const POWER_MOTOR2_TITLE = "Motor 2";
QString const POWER_MOTOR3_TITLE = "Motor 3";
QString const POWER_MOTOR4_TITLE = "Motor 4";
QString const ENCODER1_TITLE = "Encoder 0";
QString const ENCODER2_TITLE = "Encoder 1";
QString const ENCODER3_TITLE = "Encoder 2";
QString const ENCODER4_TITLE = "Encoder 3";


//sensors names
QString const ACCELEROMETER_NAME = "A";
QString const GYROSCOPE_NAME = "G";
QString const BATTERY_NAME = "B";
QString const POWER_MOTOR1_NAME = "M1";
QString const POWER_MOTOR2_NAME = "JM1";
QString const POWER_MOTOR3_NAME = "JM2";
QString const POWER_MOTOR4_NAME = "JM3";
QString const ENCODER1_NAME = "JB1";
QString const ENCODER2_NAME = "JB2";
QString const ENCODER3_NAME = "JB3";
QString const ENCODER4_NAME = "JB4";

//daemon numbers
int const TCP_PEDIOD = 10;
int const SENSORS3D_DATA_UPDATE_PERIOD = 5;
int const MOTOR_DATA_UPDATE_PERIOD = 5;
int const ENCODER_DATA_UPDATE_PERIOD = 5;
int const BATTERY_DATA_UPDATE_PERIOD = 1000;

//dashboard numbers
int const WAITING_RESPONSE_TIME = 5000;
int const TOOLBAR_WIDTH = 120;
QSize const PANEL_START_SIZE = QSize(800, 600);
QSize const PANEL_MIN_SIZE = QSize(640, 480);

//wi-fi
QString const START_IP_STRING = "192.168.1.34";
QString const START_PORT_STRING = "1221";
int const START_PORT_INT = 1221;

//shortcuts
QKeySequence const SHOW_HIDE_SHORTCUT = Qt::CTRL|Qt::Key_Q;

//commands
QString const SUBSCRIBE_STRING = "sub";
QString const UNSUBSCRIBE_STRING = "unsub";

//user messages
QString const SHOW_HIDE_TEXT = "Use Ctrl+Q for show/hide menu";
QString const WAITING_RESPONSE_MESSAGE = "Connection to TRIK: waiting responce...";
QString const NOCONNECTION_MESSAGE = "No connection: try to connect again";
QString const SEND_MESSAGE = "Dashboard connected";
QString const SEND_FROM_DAEMON_MESSAGE = "TRIK connected";
