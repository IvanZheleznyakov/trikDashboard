#include "facade.h"

Facade::Facade(ICommunicator *communicator):
    communicator(communicator)
{

}

bool Facade::connectToTRIK(QString ip, int port)
{
    communicator->setIP(ip.toLatin1());
    communicator->setPort(port);
    communicator->connectToHost();

    communicator->send(SEND_MESSAGE);

    return communicator->isConnected();
}
