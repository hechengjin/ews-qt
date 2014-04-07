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

QList<Message> SyncFolderItemsReply::create() const
{
    Q_D(const SyncFolderItemsReply);
    return d->createList;
}

QList<Message> SyncFolderItemsReply::update() const
{
    Q_D(const SyncFolderItemsReply);
    return d->updateList;
}

QStringList SyncFolderItemsReply::remove() const
{
    Q_D(const SyncFolderItemsReply);
    return d->removeList;
}

SyncFolderItemsReplyPrivate::SyncFolderItemsReplyPrivate(KDSoapJob *job) :
    ReplyPrivate(job)
{
}

void SyncFolderItemsReplyPrivate::processJob(KDSoapJob *job)
{
    SyncFolderItemsJob *syncJob = qobject_cast<SyncFolderItemsJob*>(job);
    const TNS__SyncFolderItemsResponseType &response = syncJob->syncFolderItemsResult();

    qDebug() << "===========";
    qDebug() << syncJob->reply();
    qDebug() << "===========";

    TNS__ArrayOfResponseMessagesType messages = response.responseMessages();

    QList<TNS__SyncFolderItemsResponseMessageType> responseMsgs;
    responseMsgs = messages.syncFolderItemsResponseMessage();

    foreach (const TNS__SyncFolderItemsResponseMessageType &msg, responseMsgs) {
        qDebug() << Q_FUNC_INFO << msg.serialize(QString());
        setResponseMessage(msg);

        syncState = msg.syncState();
        includesLastItemInRange = msg.includesLastItemInRange();

        T__SyncFolderItemsChangesType changes = msg.changes();
        qDebug() << "create" <<  changes.create().size();
        qDebug() << "delete" <<  changes.delete_().size();
        qDebug() << "update" <<  changes.update().size();
        foreach (const T__SyncFolderItemsCreateOrUpdateType &create, changes.create()) {
            qDebug() << Q_FUNC_INFO << create.message().subject();
            MessagePrivate *priv = new MessagePrivate(create.message());
            createList << Message(*priv);
        }

        foreach (const T__SyncFolderItemsCreateOrUpdateType &update, changes.update()) {
            qDebug() << Q_FUNC_INFO << update.item().subject();
            MessagePrivate *priv = new MessagePrivate(update.message());
            updateList << Message(*priv);
        }

        foreach (const T__SyncFolderItemsDeleteType &deleteFolder, changes.delete_()) {
            qDebug() << Q_FUNC_INFO << deleteFolder.itemId().id();
            removeList << deleteFolder.itemId().id();
        }

        qDebug() << Q_FUNC_INFO << msg.includesLastItemInRange();
        qDebug() << Q_FUNC_INFO << msg.responseCode();
        qDebug() << Q_FUNC_INFO << msg.messageText();
//        qDebug() << Q_FUNC_INFO << msg.messageXml();
//        msg.changes();
    }
}
