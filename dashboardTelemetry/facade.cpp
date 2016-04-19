#include "facade.h"
#include <QTimer>

Facade::Facade(ICommunicator *tcpCommunicator, ICommunicator *udpCommunicator) :
    mTCommunicator(tcpCommunicator),
    mUCommunicator(udpCommunicator)
{
    mParser = tcpCommunicator->getParser();
    connect(mParser, &Parser::subscribeWidgetToDataSource, this, &Facade::subscribeWidgetToDataSource);
    QTimer *timer = new QTimer();
    timer->stop();
    connect(this, &Facade::expressionIsCreated, mParser, &Parser::parseExpression);
//    connect(timer, &QTimer::timeout, mParser, &Parser::parseExpression);
    timer->start(1000);
}

bool Facade::connectToTRIK(QString ip, int port)
{
    mTCommunicator->setIP(ip.toLatin1());
    mUCommunicator->setIP(ip.toLatin1());
    mTCommunicator->setPort(port);
    mUCommunicator->setPort(port);
    mTCommunicator->connectToHost();
    mUCommunicator->connectToHost();
    mTCommunicator->send(SEND_MESSAGE);

    return mTCommunicator->isConnected() && mUCommunicator->isConnected();
}

void Facade::requestDataToSubscribe(QString widgetName, QString deviceName)
{
    mParser->requestDataToSubscribe(widgetName, deviceName);
}

void Facade::requestDataToUnscribe(QString widgetName, QString deviceName)
{
    mParser->requestDataToUnscribe(widgetName, deviceName);
}
