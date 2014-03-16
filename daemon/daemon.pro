#-------------------------------------------------
#
# Project created by QtCreator 2014-03-09T16:21:04
#
#-------------------------------------------------

TRIKCONTROL_BINDIR = ../../trikRuntime/bin/x86-debug/
TRIKCONTROL_DIR = ../../trikRuntime/trikControl

QT       += core
QT       += network
QT       -= gui

TARGET = daemon
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH = \
        $$TRIKCONTROL_DIR/include \

LIBS += -L$$TRIKCONTROL_BINDIR -ltrikControl-x86-d

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
    observer.h
