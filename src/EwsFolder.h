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

#ifndef EWSFOLDER_H
#define EWSFOLDER_H

#include "ewsexport.h"
#include "EwsEffectiveRights.h"
#include "EwsPermission.h"

#include <QObject>

namespace Ews {

class Reply;
class Connection;
class FolderPrivate;
class EWS_EXPORT Folder
{
    Q_GADGET
    Q_ENUMS(BaseShape)
    Q_ENUMS(WellKnownFolderName)
    Q_ENUMS(DeleteType)
public:
    enum BaseShape {
        IdOnly,
        Default,
        AllProperties
    };

    enum WellKnownFolderName {
        WellKnownFolderNameUnknown,
        Calendar,
        Contacts,
        DeletedItems,
        Drafts,
        Inbox,
        Journal,
        Notes,
        Outbox,
        SentItems,
        Tasks,
        MsgFolderRoot,
        PublicFoldersRoot,
        Root,
        JunkEmail,
        SearchFolders,
        VoiceMail,
        RecoverableItemsRoot,
        RecoverableItemsDeletions,
        RecoverableItemsVersions,
        RecoverableItemsPurges,
        ArchiveRoot,
        ArchiveMsgFolderRoot,
        ArchiveDeletedItems,
        ArchiveRecoverableItemsRoot,
        ArchiveRecoverableItemsDeletions,
        ArchiveRecoverableItemsVersions,
        ArchiveRecoverableItemsPurges,
        SyncIssues,
        Conflicts,
        LocalFailures,
        ServerFailures,
        RecipientCache,
        QuickContacts,
        ConversationHistory,
        ToDoSearch
    };

    enum DeleteType {
        HardDelete,
        MoveToDeletedItems,
        SoftDelete
    };

    /**
     * @brief Folder
     * @param connection
     * @param wellKnownFolderName
     * @param changeKey required on rename operation
     */
    Folder(Connection *connection, WellKnownFolderName wellKnownFolderName, const QString &changeKey = QString());

    /**
     * @brief Folder
     * @param connection
     * @param folderId
     * @param changeKey required on rename operation
     */
    Folder(Connection *connection, const QString &folderId, const QString &changeKey = QString());
    Folder(FolderPrivate *priv);
    virtual ~Folder();

    QString id() const;
    void setId(const QString &id);
    QString changeKey() const;
    void setChangeKey(const QString &changeKey);
    WellKnownFolderName wellKnownFolderName() const;
    QString wellKnownFolderNameString() const;
    QString folderClass() const;
    QString parentId() const;
    QString parentChangeKey() const;
    QString displayName() const;
    void setDisplayName(const QString &displayName);
    EffectiveRights effectiveRights() const;
    int totalCount() const;
    int unreadCount() const;
    int childFolderCount() const;
    QList<Permission> permissions() const;

    Reply *load(BaseShape folderShape) const;
    Reply *update() const;
    Reply *remove(DeleteType mode) const;

protected:
    Q_DECLARE_PRIVATE(Folder)
    FolderPrivate *d_ptr;
};

}

#endif // EWSFOLDER_H
