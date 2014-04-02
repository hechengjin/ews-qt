/*
 * Copyright (C) 2013 Daniel Nicoletti <dantti12@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 */

#ifndef EWSEMAILADDRESS_H
#define EWSEMAILADDRESS_H

#include "ewsexport.h"

#include <QString>

class EWS_EXPORT EwsEmailAddress
{
public:
    EwsEmailAddress();
//    EwsEmailAddress(/*const ESoapElement &rootElement*/);

    QString id() const;
    QString name() const;
    QString emailAddress() const;
    QString routingType() const;
    QString mailboxType() const;

private:
    QString m_id;
    QString m_name;
    QString m_emailAddress;
    QString m_routingType;
    QString m_mailboxType;
};

#endif // EWSEMAILADDRESS_H
