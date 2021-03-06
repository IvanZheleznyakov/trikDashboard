#include "udpcommunicator.h"

UdpCommunicator::UdpCommunicator(Parser *parser) :
    mPort(START_PORT_INT),
    mIp(START_IP_STRING),
    mBlockSize(0),
    mParser(parser),
    hiMessage(true)
{
    mSocket = new QUdpSocket(this);
    connect(mSocket, SIGNAL(readyRead()), this, SLOT(read()));
    connect(mSocket, &QUdpSocket::connected, this, &UdpCommunicator::setConnection);
    connect(mSocket, &QUdpSocket::disconnected, this, &UdpCommunicator::abortConnection);
    connect(this, &UdpCommunicator::recieveMessage, this->mParser, &Parser::parseMessage);
}

void UdpCommunicator::setConnection()
{
    emit newConnection();
}

void UdpCommunicator::abortConnection()
{
    emit lostConnection();
}

void UdpCommunicator::setIP(QString ipString)
{
    mIp = QHostAddress(ipString);
}

QHostAddress UdpCommunicator::getHostAddress()
{
    return mIp;
}

void UdpCommunicator::setPort(int numPort)
{
    mPort = numPort;
}

int UdpCommunicator::connectedState()
{
    return mSocket->ConnectedState;
}

void UdpCommunicator::connectToHost()
{
    mBlockSize = 0;
    mSocket->abort();
    mSocket->bind(QHostAddress::Any, mPort);
}

bool UdpCommunicator::isConnected()
{
    return (connectedState() == QUdpSocket::ConnectedState);
}

Parser *UdpCommunicator::getParser()
{
    return mParser;
}

void UdpCommunicator::send(QString message)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;
    out << message;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    mSocket->writeDatagram(block, mIp, mPort);
}

void UdpCommunicator::read()
{
    while(mSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        QString message(datagram);
        datagram.resize(mSocket->pendingDatagramSize());
        QHostAddress *address = new QHostAddress(START_IP_STRING);
        mSocket->readDatagram(datagram.data(), datagram.size(), address);
        for (int i = 0; i < datagram.size(); i++)
        {
            message += datagram.data()[i];
        }
        emit recieveMessage(message);
    }
}
