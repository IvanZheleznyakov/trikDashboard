#include "dashboard.h"
#include "tcpcommunicator.h"
#include "parser.h"
#include <QApplication>
#include <QtCore>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Parser *parser = new Parser();
    TcpCommunicator *tcpCommunicator = new TcpCommunicator(parser);
    Dashboard dashboard(tcpCommunicator);

    return app.exec();
}
