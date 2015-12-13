#-------------------------------------------------
#
# Project created by QtCreator 2015-12-12T19:50:25
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dashboardTelemetry
TEMPLATE = app


SOURCES += \
    controlpanel.cpp \
    dashboard.cpp \
    facade.cpp \
    main.cpp \
    toolbar.cpp \
    tcpcommunicator.cpp \
    parser.cpp

HEADERS  += \
    controlpanel.h \
    dashboard.h \
    facade.h \
    telemetry_const.h \
    toolbar.h \
    icommunicator.h \
    tcpcommunicator.h \
    parser.h
