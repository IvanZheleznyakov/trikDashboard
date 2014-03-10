#include "tcpcommunicator.h"

TcpCommunicator::TcpCommunicator(QObject *parent) :
    QObject(parent),
    port(1111),
    ip("192.254.254.254"),
    blockSize(0)
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
}

void TcpCommunicator::setIP(QString ipString)
{
    ip = ipString;
}

void TcpCommunicator::setPort(int numPort)
{
    port = numPort;
}

void TcpCommunicator::connectToHost()
{
    blockSize = 0;
    socket->abort();
    socket->connectToHost(ip, port);
}

void TcpCommunicator::send(QString message)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;
    out << message;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    socket->write(block);
}

void TcpCommunicator::read()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_4_0);
    QString message;

    for (;;)
    {
        if (!blockSize)
        {
            if (socket->bytesAvailable() < sizeof(quint16))
            {
                break;
            }
            in >> blockSize;
        }
        if (socket->bytesAvailable() < blockSize)
        {
            break;
        }
        in >> message;
        blockSize = 0;
        emit recieveMessage(message);
    }
}
