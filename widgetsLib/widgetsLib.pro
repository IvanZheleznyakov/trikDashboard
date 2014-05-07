#-------------------------------------------------
#
# Project created by QtCreator 2014-05-05T18:52:41
#
#-------------------------------------------------

QT       += widgets
QT       += printsupport

TARGET = widgetsLib
TEMPLATE = lib

DEFINES += WIDGETSLIB_LIBRARY

SOURCES += dashboardwidget.cpp \
    qcustomplot.cpp \
    customplotwidget.cpp

HEADERS += dashboardwidget.h\
        widgetslib_global.h \
    qcustomplot.h \
    customplotwidget.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
