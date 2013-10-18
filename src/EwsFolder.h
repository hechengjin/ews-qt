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
#include "ESoapElement.h"
#include "EwsEffectiveRights.h"
#include "EwsPermission.h"

class EwsReply;
class EwsConnection;
class EWS_EXPORT EwsFolder
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
     * @brief EwsFolder
     * @param connection
     * @param wellKnownFolderName
     * @param changeKey required on rename operation
     */
    EwsFolder(EwsConnection *connection, WellKnownFolderName wellKnownFolderName, const QString &changeKey = QString());

    /**
     * @brief EwsFolder
     * @param connection
     * @param folderId
     * @param changeKey required on rename operation
     */
    EwsFolder(EwsConnection *connection, const QString &folderId, const QString &changeKey = QString());
    EwsFolder(const ESoapElement &rootElement);

    QString id() const;
    QString changeKey() const;
    WellKnownFolderName wellKnownFolderName() const;
    QString wellKnownFolderNameString() const;
    QString folderClass() const;
    QString parentId() const;
    QString parentChangeKey() const;
    QString displayName() const;
    void setDisplayName(const QString &displayName);
    EwsEffectiveRights effectiveRights() const;
    int totalCount() const;
    int unreadCount() const;
    int childFolderCount() const;
    QList<EwsPermission> permissions() const;

    EwsReply *load(BaseShape folderShape) const;
    EwsReply *update() const;
    EwsReply *remove(DeleteType mode) const;

private:
    WellKnownFolderName m_wellKnownFolderName;
    QString m_id;
    QString m_changeKey;
    QString m_folderClass;
    QString m_parentId;
    QString m_parentChangeKey;
    QString m_displayName;
    EwsEffectiveRights m_effectiveRights;
    int m_totalCount;
    int m_unreadCount;
    int m_childFolderCount;
    QList<EwsPermission> m_permissions;
    QHash<QString, QString> m_changes;
    EwsConnection *m_connection;
};

#endif // EWSFOLDER_H
