#-------------------------------------------------
#
# Project created by QtCreator 2014-03-09T18:25:24
#
#-------------------------------------------------


WIDGETSLIB_BINDIR = ../widgetsLib/debug/
WIDGETSLIB_DIR = ../widgetsLib/

QT       += core gui
QT       += network
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dashboard
TEMPLATE = app

INCLUDEPATH = \
        $$WIDGETSLIB_DIR \

LIBS += -L$$WIDGETSLIB_BINDIR -lwidgetsLib


SOURCES += main.cpp\
    dashboard.cpp \
    tcpcommunicator.cpp \
    controlpanel.cpp \
    toolbar.cpp \
    sensor.cpp

HEADERS  += dashboard.h \
    tcpcommunicator.h \
    controlpanel.h \
    toolbar.h \
    sensor.h \
    dashboard_const.h
