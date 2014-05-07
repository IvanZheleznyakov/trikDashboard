#-------------------------------------------------
#
# Project created by QtCreator 2014-03-09T18:25:24
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dashboard
TEMPLATE = app


SOURCES += main.cpp\
        dashboard.cpp \
    tcpcommunicator.cpp \
    controlpanel.cpp \
    toolbar.cpp

HEADERS  += dashboard.h \
    tcpcommunicator.h \
    controlpanel.h \
    toolbar.h
