/*
 * Copyright (C) 2013-2014 Daniel Nicoletti <dantti12@gmail.com>
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

#include "syncfolderitemsreply_p.h"
#include "wsdl_Services.h"

#include <QDebug>

using namespace Ews;

SyncFolderItemsReply::SyncFolderItemsReply(SyncFolderItemsReplyPrivate *priv) :
    Reply(priv)
{
}

QString SyncFolderItemsReply::responseCode() const
{
    Q_D(const SyncFolderItemsReply);
    return d->responseCode;
}

QString SyncFolderItemsReply::syncState() const
{
    Q_D(const SyncFolderItemsReply);
    return d->syncState;
}

bool SyncFolderItemsReply::includesLastItemInRange() const
{
    Q_D(const SyncFolderItemsReply);
    return d->includesLastItemInRange;
}

SyncFolderItemsReplyPrivate::SyncFolderItemsReplyPrivate(KDSoapJob *job) :
    ReplyPrivate(job)
{
}

void SyncFolderItemsReplyPrivate::processJob(KDSoapJob *job)
{
    SyncFolderItemsJob *syncJob = qobject_cast<SyncFolderItemsJob*>(job);
    const TNS__SyncFolderItemsResponseType &response = syncJob->syncFolderItemsResult();

    TNS__ArrayOfResponseMessagesType messages = response.responseMessages();

    QList<TNS__SyncFolderItemsResponseMessageType> responseMsgs;
    responseMsgs = messages.syncFolderItemsResponseMessage();

    foreach (const TNS__SyncFolderItemsResponseMessageType &msg, responseMsgs) {
        qDebug() << Q_FUNC_INFO << msg.serialize(QString());
        syncState = msg.syncState();
        includesLastItemInRange = msg.includesLastItemInRange();
        responseCode = msg.responseCode();
        messageText = msg.messageText();

        T__SyncFolderItemsChangesType changes = msg.changes();
        qDebug() << "create" <<  changes.create().size();
        qDebug() << "delete" <<  changes.delete_().size();
        qDebug() << "update" <<  changes.update().size();
        foreach (const T__SyncFolderItemsCreateOrUpdateType &create, changes.create()) {
            qDebug() << create.item().subject();
//            createFolders << folder;
        }

        foreach (const T__SyncFolderItemsCreateOrUpdateType &update, changes.update()) {
            qDebug() << Q_FUNC_INFO << update.item().subject();
//            updateFolders << folder;
        }

        foreach (const T__SyncFolderItemsDeleteType &deleteFolder, changes.delete_()) {
            qDebug() << Q_FUNC_INFO << deleteFolder.itemId().id();
            deleteItems << deleteFolder.itemId().id();
        }

        qDebug() << Q_FUNC_INFO << msg.includesLastItemInRange();
        qDebug() << Q_FUNC_INFO << msg.responseCode();
        qDebug() << Q_FUNC_INFO << msg.messageText();
//        qDebug() << Q_FUNC_INFO << msg.messageXml();
//        msg.changes();
    }
}
