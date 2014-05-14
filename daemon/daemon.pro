#-------------------------------------------------
#
# Project created by QtCreator 2014-03-09T16:21:04
#
#-------------------------------------------------

TRIKCONTROL_BINDIR = ../../trikRuntime/bin/arm-release
TRIKCONTROL_DIR = ../../trikRuntime/trikControl

QT       += core
QT       += network
QT       += gui

TARGET = daemon
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH = \
        $$TRIKCONTROL_DIR/include \
        ../telemetry/ \

LIBS += -L$$TRIKCONTROL_BINDIR -ltrikControl

!macx {
        QMAKE_LFLAGS += -Wl,-O1,-rpath,.
}

SOURCES += main.cpp \
    daemon.cpp \
    tcpcommunicator.cpp \
    observer.cpp
HEADERS += \
    daemon.h \
    tcpcommunicator.h \
    observer.h \
    ../telemetry/telemetry_const.h
