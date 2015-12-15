#include "facade.h"

Facade::Facade(ICommunicator *communicator) :
    mCommunicator(communicator)
{
    mParser = communicator->getParser();
    connect(mParser, &Parser::subscribeWidgetToDataSource, this, &Facade::subscribeWidgetToDataSource);
}

bool Facade::connectToTRIK(QString ip, int port)
{
    mCommunicator->setIP(ip.toLatin1());
    mCommunicator->setPort(port);
    mCommunicator->connectToHost();

    mCommunicator->send(SEND_MESSAGE);

    return mCommunicator->isConnected();
}

void Facade::requestDataToSubscribe(QString widgetName, QString deviceName)
{
    mParser->requestDataToSubscribe(widgetName, deviceName);
}

void Facade::requestDataToUnscribe(QString, QString)
{

}
