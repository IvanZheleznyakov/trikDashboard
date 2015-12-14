#include "facade.h"

Facade::Facade(ICommunicator *communicator) :
    communicator(communicator)
{
    parser = communicator->getParser();
}

bool Facade::connectToTRIK(QString ip, int port)
{
    communicator->setIP(ip.toLatin1());
    communicator->setPort(port);
    communicator->connectToHost();

    communicator->send(SEND_MESSAGE);

    return communicator->isConnected();
}
