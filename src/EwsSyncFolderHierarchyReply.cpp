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

#include "EwsSyncFolderHierarchyReply.h"
#include "EwsSyncFolderHierarchyReply_p.h"

#include <QDebug>

EwsSyncFolderHierarchyReply::EwsSyncFolderHierarchyReply(QNetworkReply *reply) :
    EwsReply(reply, QLatin1String("SyncFolderHierarchy"))
{
}

EwsSyncFolderHierarchyReply::EwsSyncFolderHierarchyReply(void *reply) :
    EwsReply(reply),
    d_ptr(new EwsSyncFolderHierarchyReplyPrivate)
{
    ExchangeServices *service = static_cast<ExchangeServices*>(reply);

    connect(service, SIGNAL(syncFolderHierarchyDone(TNS__SyncFolderHierarchyResponseType)),
            d_ptr, SLOT(syncFolderHierarchyDone(TNS__SyncFolderHierarchyResponseType)));
    connect(service, SIGNAL(syncFolderHierarchyError(KDSoapMessage)),
            d_ptr, SLOT(syncFolderHierarchyError(KDSoapMessage)));
}

QString EwsSyncFolderHierarchyReply::responseCode() const
{
    Q_D(const EwsSyncFolderHierarchyReply);
    return d->responseCode;
}

QString EwsSyncFolderHierarchyReply::syncState() const
{
    Q_D(const EwsSyncFolderHierarchyReply);
    return d->syncState;
}

bool EwsSyncFolderHierarchyReply::includesLastFolderInRange() const
{
    Q_D(const EwsSyncFolderHierarchyReply);
    return d->includesLastFolderInRange;
}

QList<EwsFolder> EwsSyncFolderHierarchyReply::createFolders() const
{
    Q_D(const EwsSyncFolderHierarchyReply);
    return d->createFolders;
}

QList<EwsFolder> EwsSyncFolderHierarchyReply::updateFolders() const
{
    Q_D(const EwsSyncFolderHierarchyReply);
    return d->updateFolders;
}

QStringList EwsSyncFolderHierarchyReply::deleteFolders() const
{
    Q_D(const EwsSyncFolderHierarchyReply);
    return d->deleteFolders;
}

bool EwsSyncFolderHierarchyReply::parseDocument(ESoapElement &response)
{
//    ESoapElement element;
//    element = response.firstChildTypedElement(QLatin1String("SyncState"), EWS_MESSAGES_NS);
//    if (!element.isNull()) {
//        m_syncState = element.text();
//    }

//    element = response.firstChildTypedElement(QLatin1String("IncludesLastFolderInRange"), EWS_MESSAGES_NS);
//    if (!element.isNull()) {
//        m_includesLastFolderInRange = element.text() == QLatin1String("true");
//    }

//    element = response.firstChildTypedElement(QLatin1String("ResponseCode"), EWS_MESSAGES_NS);
//    if (!element.isNull()) {
//        m_responseCode = element.text();
//    }

//    element = response.firstChildTypedElement(QLatin1String("MessageText"), EWS_MESSAGES_NS);
//    if (!element.isNull()) {
//        m_messageText = element.text();
//    }

//    ESoapElement changes = response.firstChildTypedElement(QLatin1String("Changes"), EWS_MESSAGES_NS);
//    if (!changes.isNull()) {
//        element = changes.firstChildElement();
//        while (!element.isNull()) {
//            if (element.equalNS(QLatin1String("Create"), EWS_TYPES_NS)) {
//                ESoapElement childElement = element.firstChildElement();
//                if (childElement.equalNS(QLatin1String("Folder"), EWS_TYPES_NS)) {
//                    m_createFolders << EwsFolder(childElement);
//                }
//            } else if (element.equalNS(QLatin1String("Update"), EWS_TYPES_NS)) {
//                ESoapElement childElement = element.firstChildElement();
//                if (childElement.equalNS(QLatin1String("Folder"), EWS_TYPES_NS)) {
//                    m_updateFolders << EwsFolder(childElement);
//                }
//            } else if (element.equalNS(QLatin1String("Delete"), EWS_TYPES_NS)) {
//                ESoapElement childElement = element.firstChildElement();
//                m_deleteFolders << childElement.attribute(QLatin1String("Id"));
//            } else {
//                qWarning() << Q_FUNC_INFO << "Unknown Changes child:" <<  element.nodeName();
//            }

//            element = element.nextSiblingElement();
//        }
//    }

    return true;
}


EwsSyncFolderHierarchyReplyPrivate::EwsSyncFolderHierarchyReplyPrivate() :
    includesLastFolderInRange(false)
{

}

void EwsSyncFolderHierarchyReplyPrivate::syncFolderHierarchyDone(const TNS__SyncFolderHierarchyResponseType &response)
{
    TNS__ArrayOfResponseMessagesType messages = response.responseMessages();

    QList<TNS__SyncFolderHierarchyResponseMessageType> responseMsgs;
    responseMsgs = messages.syncFolderHierarchyResponseMessage();

    foreach (const TNS__SyncFolderHierarchyResponseMessageType &msg, responseMsgs) {
        qDebug() << Q_FUNC_INFO << msg.serialize(QString());
        syncState = msg.syncState();
        includesLastFolderInRange = msg.includesLastFolderInRange();
        responseCode = msg.responseCode();
        messageText = msg.messageText();

        T__SyncFolderHierarchyChangesType changes = msg.changes();
        qDebug() << "create" <<  changes.create().size();
        qDebug() << "delete" <<  changes.delete_().size();
        qDebug() << "update" <<  changes.update().size();
        foreach (const T__SyncFolderHierarchyCreateOrUpdateType &create, changes.create()) {
            qDebug() << create.folder().displayName();
        }

        foreach (const T__SyncFolderHierarchyCreateOrUpdateType &create, changes.create()) {
            qDebug() << Q_FUNC_INFO << create.calendarFolder().displayName();
        }
        qDebug() << Q_FUNC_INFO << msg.includesLastFolderInRange();
        qDebug() << Q_FUNC_INFO << msg.responseCode();
        qDebug() << Q_FUNC_INFO << msg.messageText();
//        qDebug() << Q_FUNC_INFO << msg.messageXml();
//        msg.changes();
    }
}

void EwsSyncFolderHierarchyReplyPrivate::syncFolderHierarchyError(const KDSoapMessage &fault)
{
    qDebug() << Q_FUNC_INFO << fault.faultAsString();
}

#include "moc_EwsSyncFolderHierarchyReply.cpp"
