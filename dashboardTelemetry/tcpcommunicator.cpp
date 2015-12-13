#include "tcpcommunicator.h"

TcpCommunicator::TcpCommunicator(Parser *parser) :
    port(START_PORT_INT),
    ip(START_IP_STRING),
    blockSize(0),
    parser(parser)
{
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &TcpCommunicator::read);
    connect(socket, &QTcpSocket::connected, this, &TcpCommunicator::setConnection);
    connect(socket, &QTcpSocket::disconnected, this, &TcpCommunicator::abortConnection);
    connect(this, &TcpCommunicator::recieveMessage, this->parser, &Parser::parseMessage);
}

void TcpCommunicator::setConnection()
{
    emit newConnection();
}

void TcpCommunicator::abortConnection()
{
    emit lostConnection();
}

void TcpCommunicator::setIP(QString ipString)
{
    ip = ipString;
}

void TcpCommunicator::setPort(int numPort)
{
    port = numPort;
}

int TcpCommunicator::connectedState()
{
    return socket->ConnectedState;
}

void TcpCommunicator::connectToHost()
{
    blockSize = 0;
    socket->abort();
    socket->connectToHost(ip, port);
}

bool TcpCommunicator::isConnected()
{
    return (connectedState() == QTcpSocket::ConnectedState);
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
