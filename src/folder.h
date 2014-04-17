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

#include "export.h"
#include "permission.h"

#include <QSharedDataPointer>

namespace Ews {

class Reply;
class GetFolderReply;
class Connection;
class FolderPrivate;
class EffectiveRights;
class EWS_EXPORT Folder
{
public:
    enum BaseShape {
        IdOnly,
        Default,
        AllProperties
    };

    enum DeleteType {
        HardDelete,
        MoveToDeletedItems,
        SoftDelete
    };

    Folder &operator=(const Folder &);

    QString id() const;
    void setId(const QString &id);
    QString changeKey() const;
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

    /**
     * @brief isDirty
     * @return returns if the class has been modified
     */
    bool isDirty() const;

    GetFolderReply *load(BaseShape folderShape) const;
    Reply *update() const;
    Reply *remove(DeleteType mode) const;

    /**
     * @brief Folder
     * @param connection
     * @param folderId
     * @param changeKey required on rename operation
     */
    Folder(Connection *connection, const QString &folderId, const QString &changeKey = QString());
    Folder(const Folder &other);
    virtual ~Folder();

protected:
    Folder(FolderPrivate &d);

    QSharedDataPointer<FolderPrivate> d_ptr;

private:
    friend class SyncFolderHierarchyReplyPrivate;
    friend class GetFolderReplyPrivate;

    // Q_DECLARE_PRIVATE equivalent for shared data pointers
    FolderPrivate* d_func();
    inline const FolderPrivate* d_func() const
    {
        return d_ptr.constData();
    }
};

}

#endif // EWSFOLDER_H
