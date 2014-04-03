#ifndef EWSCONNECTION_P_H
#define EWSCONNECTION_P_H

#include "EwsConnection.h"

class ExchangeServices;
namespace Ews {

class ConnectionPrivate
{
public:
    ExchangeServices *service;
    Connection::ServerVersion serverVersion;
    QUrl uri;
};

}

#endif // EWSCONNECTION_P_H
