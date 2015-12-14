#include "facade.h"

Facade::Facade(ICommunicator *communicator) :
    mCommunicator(communicator)
{
    mParser = communicator->getParser();
}

bool Facade::connectToTRIK(QString ip, int port)
{
    mCommunicator->setIP(ip.toLatin1());
    mCommunicator->setPort(port);
    mCommunicator->connectToHost();

    mCommunicator->send(SEND_MESSAGE);

    return mCommunicator->isConnected();
}
