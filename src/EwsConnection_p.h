#ifndef EWSCONNECTION_P_H
#define EWSCONNECTION_P_H

#include "EwsConnection.h"

class ExchangeServices;
class EwsConnectionPrivate
{
public:
    ExchangeServices *service;
    EwsConnection::ServerVersion serverVersion;
    QUrl uri;
};

#endif // EWSCONNECTION_P_H
