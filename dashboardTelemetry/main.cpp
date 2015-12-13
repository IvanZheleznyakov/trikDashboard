#include "dashboard.h"
#include "tcpcommunicator.h"
#include <QApplication>
#include <QtCore>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    TcpCommunicator *tcpCommunicator = new TcpCommunicator();
    Dashboard dashboard(tcpCommunicator);

    return app.exec();
}
