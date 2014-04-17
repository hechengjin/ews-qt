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

#include "getfolderreply_p.h"
#include "wsdl_Services.h"

#include <QDebug>

using namespace Ews;

GetFolderReply::GetFolderReply(GetFolderReplyPrivate *priv) :
    Reply(priv)
{
}

GetFolderReplyPrivate::GetFolderReplyPrivate(KDSoapJob *job) :
    ReplyPrivate(job, this)
{
}

QList<Folder> GetFolderReply::folders() const
{
    Q_D(const GetFolderReply);
    return d->foldersList;
}

void GetFolderReplyPrivate::processJob(KDSoapJob *job)
{
    GetFolderJob *syncJob = qobject_cast<GetFolderJob*>(job);
    const TNS__GetFolderResponseType &response = syncJob->getFolderResult();

    TNS__ArrayOfResponseMessagesType messages = response.responseMessages();

    QList<TNS__FolderInfoResponseMessageType> responseMsgs;
    responseMsgs = messages.getFolderResponseMessage();

    foreach (const TNS__FolderInfoResponseMessageType &msg, responseMsgs) {
        setResponseMessage(msg);

        T__ArrayOfFoldersType folders = msg.folders();
        foreach (const T__FolderType &folder, folders.folder()) {
            FolderPrivate *priv = new FolderPrivate(folder);
            foldersList << Folder(*priv);
        }
    }
}
