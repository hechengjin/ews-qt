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

#include "emailaddress.h"
#include "request.h"

#include <QDebug>

using namespace Ews;

EmailAddress::EmailAddress()
{
}

//EmailAddress::EmailAddress(const ESoapElement &rootElement)
//{
//    ESoapElement element;

//    element = rootElement.firstChildElement();
//    while (!element.isNull()) {
//        if (element.equalNS(QLatin1String("Name"), EWS_TYPES_NS)) {
//            m_name = element.text();
//        } else if (element.equalNS(QLatin1String("EmailAddress"), EWS_TYPES_NS)) {
//            m_emailAddress = element.text();
//        } else if (element.equalNS(QLatin1String("RoutingType"), EWS_TYPES_NS)) {
//            m_routingType = element.text();
//        } else if (element.equalNS(QLatin1String("MailboxType"), EWS_TYPES_NS)) {
//            m_mailboxType = element.text();
//        } else if (element.equalNS(QLatin1String("ItemId"), EWS_TYPES_NS)) {
//             m_id = element.text();
//        } else {
//            // TODO create PermissionSet class
//            qWarning() << Q_FUNC_INFO << "element unknown" << element.nodeName();
//        }

//        element = element.nextSiblingElement();
//    }
//}

QString EmailAddress::id() const
{
    return m_id;
}

QString EmailAddress::name() const
{
    return m_name;
}

QString EmailAddress::emailAddress() const
{
    return m_emailAddress;
}

QString EmailAddress::routingType() const
{
    return m_routingType;
}

QString EmailAddress::mailboxType() const
{
    return m_mailboxType;
}
