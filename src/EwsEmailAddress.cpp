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

#include "EwsEmailAddress.h"
#include "EwsRequest.h"

#include <QDebug>

EwsEmailAddress::EwsEmailAddress()
{
}

//EwsEmailAddress::EwsEmailAddress(const ESoapElement &rootElement)
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

QString EwsEmailAddress::id() const
{
    return m_id;
}

QString EwsEmailAddress::name() const
{
    return m_name;
}

QString EwsEmailAddress::emailAddress() const
{
    return m_emailAddress;
}

QString EwsEmailAddress::routingType() const
{
    return m_routingType;
}

QString EwsEmailAddress::mailboxType() const
{
    return m_mailboxType;
}
