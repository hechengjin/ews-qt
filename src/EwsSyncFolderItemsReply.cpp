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

#include "EwsSyncFolderItemsReply.h"

#include <QDebug>

EwsSyncFolderItemsReply::EwsSyncFolderItemsReply(QNetworkReply *reply) :
    EwsReply(reply, QLatin1String("SyncFolderItems"))
{
}

QString EwsSyncFolderItemsReply::responseCode() const
{
    return m_responseCode;
}

QString EwsSyncFolderItemsReply::syncState() const
{
    return m_syncState;
}

bool EwsSyncFolderItemsReply::includesLastItemInRange() const
{
    return m_includesLastItemInRange;
}

QList<EwsMessage> EwsSyncFolderItemsReply::createMessages() const
{
    return m_createMessages;
}

bool EwsSyncFolderItemsReply::parseDocument(ESoapElement &response)
{
    ESoapElement element;
    element = response.firstChildTypedElement(QLatin1String("SyncState"), EWS_MESSAGES_NS);
    if (!element.isNull()) {
        m_syncState = element.text();
    }

    element = response.firstChildTypedElement(QLatin1String("IncludesLastItemInRange"), EWS_MESSAGES_NS);
    if (!element.isNull()) {
        m_includesLastItemInRange = element.text() == QLatin1String("true");
    }

    element = response.firstChildTypedElement(QLatin1String("ResponseCode"), EWS_MESSAGES_NS);
    if (!element.isNull()) {
        m_responseCode = element.text();
    }

    element = response.firstChildTypedElement(QLatin1String("MessageText"), EWS_MESSAGES_NS);
    if (!element.isNull()) {
        m_messageText = element.text();
    }

    ESoapElement changes = response.firstChildTypedElement(QLatin1String("Changes"), EWS_MESSAGES_NS);
    if (!changes.isNull()) {
        element = changes.firstChildElement();
        while (!element.isNull()) {
            if (element.equalNS(QLatin1String("Create"), EWS_TYPES_NS)) {
                ESoapElement childElement = element.firstChildElement();
                if (childElement.equalNS(QLatin1String("Message"), EWS_TYPES_NS)) {
                    m_createMessages << EwsMessage(childElement);
                }
            } else {
                qWarning() << Q_FUNC_INFO << "Unknown Changes child:" <<  element.nodeName();
            }

            element = element.nextSiblingElement();
        }
    } else {
        qWarning() << Q_FUNC_INFO << "Changes is null";
    }

    return true;
}
