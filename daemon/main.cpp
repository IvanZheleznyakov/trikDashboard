#include <QCoreApplication>
#include "daemon.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString configPath = "config.xml";
    Daemon daemon(a.thread(), configPath);

    return a.exec();
}
