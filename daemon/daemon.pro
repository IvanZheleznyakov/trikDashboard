#-------------------------------------------------
#
# Project created by QtCreator 2014-03-09T16:21:04
#
#-------------------------------------------------

QT       += core
QT       += network
QT       -= gui

TARGET = daemon
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    daemon.cpp \
    tcpcommunicator.cpp

HEADERS += \
    daemon.h \
    tcpcommunicator.h
