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
    customplotwidget.cpp \
    emptywidget.cpp \
    lcdnumberwidget.cpp \
    progressbarwidget.cpp \
    tablewidget.cpp

HEADERS += dashboardwidget.h\
        widgetslib_global.h \
    qcustomplot.h \
    customplotwidget.h \
    emptywidget.h \
    lcdnumberwidget.h \
    progressbarwidget.h \
    tablewidget.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
