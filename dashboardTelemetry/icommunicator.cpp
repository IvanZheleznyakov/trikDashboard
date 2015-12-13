#include "icommunicator.h"

int ICommunicator::getPort() const
{
    return port;
}

QString ICommunicator::getIp() const
{
    return ip;
}

void ICommunicator::setIp(const QString &value)
{
    ip = value;
}

