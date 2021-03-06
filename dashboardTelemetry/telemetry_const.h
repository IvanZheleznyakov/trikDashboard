#pragma once
#include <QObject>
#include <QString>
#include <QKeySequence>
#include <QSize>

class TelemetryConst : public QObject
{
    Q_OBJECT
public:
    //dashboard names
    static QString const ACCELEROMETER_TITLE() { return tr("Accelerometer"); }
    static QString const GYROSCOPE_TITLE() { return tr("Gyroscope"); }
    static QString const BATTERY_TITLE() { return tr("Battery"); }
    static QString const POWER_MOTOR1_TITLE() { return tr("Motor 1"); }
    static QString const POWER_MOTOR2_TITLE() { return tr("Motor 2"); }
    static QString const POWER_MOTOR3_TITLE() { return tr("Motor 3"); }
    static QString const POWER_MOTOR4_TITLE() { return ("Motor 4"); }
    static QString const ENCODER1_TITLE() { return tr("Encoder 0"); }
    static QString const ENCODER2_TITLE() { return tr("Encoder 1"); }
    static QString const ENCODER3_TITLE() { return tr("Encoder 2"); }
    static QString const ENCODER4_TITLE() { return tr("Encoder 3"); }

    //widgets names
    static QString const PLOT_TITLE() { return tr("Plot"); }
    static QString const LCDNUMBER_TITLE() { return tr("LCD Number"); }
    static QString const PROGRESSBAR_TITLE() { return tr("Progress bar"); }
    static QString const TABLE_TITLE() { return tr("Table"); }

    //user messages
    static QString const SHOW_HIDE_TEXT() { return tr("Use Ctrl+Q for show/hide menu"); }
    static QString const WAITING_RESPONSE_MESSAGE() { return tr("Connection to TRIK: waiting responce..."); }
    static QString const NOCONNECTION_MESSAGE() { return tr("No connection: try to connect again"); }
    static QString const SEND_FROM_DAEMON_MESSAGE() { return tr("TRIK connected"); }
};

//sensors names
QString const ACCELEROMETER_NAME = "A";
QString const ACCELEROMETER_NAME_FIRST = "A1";
QString const ACCELEROMETER_NAME_SECOND = "A2";
QString const ACCELEROMETER_NAME_THIRD = "A3";
QString const GYROSCOPE_NAME = "G";
QString const GYROSCOPE_NAME_FIRST = "G1";
QString const GYROSCOPE_NAME_SECOND = "G2";
QString const GYROSCOPE_NAME_THIRD = "G3";
QString const BATTERY_NAME = "B";
QString const POWER_MOTOR1_NAME = "M1";
QString const POWER_MOTOR2_NAME = "M2";
QString const POWER_MOTOR3_NAME = "M3";
QString const POWER_MOTOR4_NAME = "M4";
QString const ENCODER1_NAME = "E1";
QString const ENCODER2_NAME = "E2";
QString const ENCODER3_NAME = "E3";
QString const ENCODER4_NAME = "E4";

//daemon numbers
int const TCP_PEDIOD = 10;
int const SENSORS3D_DATA_UPDATE_PERIOD = 5;
int const MOTOR_DATA_UPDATE_PERIOD = 5;
int const ENCODER_DATA_UPDATE_PERIOD = 5;
int const BATTERY_DATA_UPDATE_PERIOD = 1000;

//dashboard numbers
int const WAITING_RESPONSE_TIME = 5000;
int const TOOLBAR_WIDTH = 150;
int const IPTEXT_HEIGHT = 24;
int const PORTTEXT_HEIGHT = 24;
QSize const PANEL_START_SIZE = QSize(800, 600);
QSize const PANEL_MIN_SIZE = QSize(640, 480);

//wi-fi
QString const START_IP_STRING = "192.168.1.34";
QString const START_PORT_STRING = "1221";
int const START_PORT_INT = 1221;
QString const LOCAL_IP_STRING = "127.0.0.1";

//shortcuts
QKeySequence const SHOW_HIDE_SHORTCUT = Qt::CTRL|Qt::Key_Q;

//commands
QString const SUBSCRIBE_STRING = "sub";
QString const UNSUBSCRIBE_STRING = "unsub";
QString const SEND_MESSAGE = "Dashboard connected";
