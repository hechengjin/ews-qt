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

#include "EwsSyncFolderHierarchyReply_p.h"
#include "EwsFolder_p.h"

#include <QDebug>

EwsSyncFolderHierarchyReply::EwsSyncFolderHierarchyReply(EwsSyncFolderHierarchyReplyPrivate *priv) :
    EwsReply(priv),
    d_ptr(priv)
{
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

EwsSyncFolderHierarchyReplyPrivate::EwsSyncFolderHierarchyReplyPrivate(KDSoapJob *job) :
    EwsReplyPrivate(job),
    includesLastFolderInRange(false)
{

}

void EwsSyncFolderHierarchyReplyPrivate::syncFolderHierarchyDone(KDSoapJob *job)
{
    if (job->isFault()) {
        qWarning() << Q_FUNC_INFO << "Failed" << job->faultAsString();
        return;
    }

    SyncFolderHierarchyJob *syncJob = qobject_cast<SyncFolderHierarchyJob*>(job);
    const TNS__SyncFolderHierarchyResponseType &response = syncJob->syncFolderHierarchyResult();

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
            qDebug() << Q_FUNC_INFO << create.folder().displayName();
            createFolders << EwsFolder(new EwsFolderPrivate(create.folder()));
        }

        foreach (const T__SyncFolderHierarchyCreateOrUpdateType &update, changes.update()) {
            qDebug() << Q_FUNC_INFO << update.folder().displayName();
            updateFolders << EwsFolder(new EwsFolderPrivate(update.folder()));
        }

        foreach (const T__SyncFolderHierarchyDeleteType &deleteFolder, changes.delete_()) {
            qDebug() << Q_FUNC_INFO << deleteFolder.folderId().id();
            deleteFolders << deleteFolder.folderId().id();
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
