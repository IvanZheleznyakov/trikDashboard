#include "dashboard.h"
#include <QApplication>
#include <QtCore>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    /*
    QTranslator myTranslator;
    myTranslator.load("dashboard_ru");
    app.installTranslator(&myTranslator);
    */
    Dashboard w;

    return app.exec();
}
