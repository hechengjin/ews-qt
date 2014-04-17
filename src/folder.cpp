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

#include "folder_p.h"

#include "request.h"
#include "connection_p.h"
#include "effectiverights_p.h"
#include "permission_p.h"
#include "reply_p.h"
#include "utils.h"

#include <QMetaEnum>
#include <QStringBuilder>
#include <QDebug>

using namespace Ews;

Folder::Folder(Connection *connection, const QString &folderId, const QString &changeKey)
    : d_ptr(new FolderPrivate)
{
    Q_D(Folder);
    d->connection = connection;
}

Folder::Folder(const Folder &other)
    : d_ptr(other.d_ptr)
{
}

Folder::Folder(FolderPrivate &priv)
    : d_ptr(&priv)
{

}

FolderPrivate *Folder::d_func()
{
    return d_ptr.data();
}

Folder::~Folder()
{
}

Folder &Folder::operator=(const Folder &folder)
{
    d_ptr = folder.d_ptr;
    return *this;
}

QString Folder::id() const
{
    Q_D(const Folder);
    return d->folder.folderId().id();
}

void Folder::setId(const QString &id)
{
    Q_D(Folder);
    d->dirty = true;
    // TODO have our own
    T__FolderIdType fId;
    fId.setId(id);
    d->folder.setFolderId(fId);
}

QString Folder::changeKey() const
{
    Q_D(const Folder);
    return d->folder.folderId().changeKey();
}

QString Folder::folderClass() const
{
    Q_D(const Folder);
    return d->folder.folderClass();
}

QString Folder::parentId() const
{
    Q_D(const Folder);
    return d->folder.parentFolderId().id();
}

QString Folder::parentChangeKey() const
{
    Q_D(const Folder);
    return d->folder.parentFolderId().changeKey();
}

QString Folder::displayName() const
{
    Q_D(const Folder);
    return d->folder.displayName();
}

void Folder::setDisplayName(const QString &displayName)
{
    Q_D(Folder);
    d->dirty = true;
    d->folder.setDisplayName(displayName);
}

EffectiveRights Folder::effectiveRights() const
{
    Q_D(const Folder);
    return d->effectiveRights;
}

int Folder::totalCount() const
{
    Q_D(const Folder);
    return d->folder.totalCount();
}

int Folder::unreadCount() const
{
    Q_D(const Folder);
    return d->folder.unreadCount();
}

int Folder::childFolderCount() const
{
    Q_D(const Folder);
    return d->folder.childFolderCount();
}

QList<Permission> Folder::permissions() const
{
    Q_D(const Folder);
    return d->permissions;
}

bool Folder::isDirty() const
{
    Q_D(const Folder);
    return d->dirty;
}

GetFolderReply *Folder::load(BaseShape folderShape) const
{
    Q_D(const Folder);
    return d->connection->getFolders(QList<Folder>() << *this, folderShape);
}

Reply *Folder::update() const
{
    Q_D(const Folder);

    TNS__UpdateFolderType request;

    T__NonEmptyArrayOfFolderChangesType folderChanges;
    T__FolderChangeType changes;

    T__FolderIdType folderId;
    folderId.setId(id());
    if (!changeKey().isEmpty()) {
        folderId.setChangeKey(changeKey());
    }
    changes.setFolderId(folderId);

    T__NonEmptyArrayOfFolderChangeDescriptionsType updates;
    QHash<QString, QString>::ConstIterator i = d->changes.begin();
    while (i != d->changes.end()) {
//        updates.setFolderField();
        ++i;
    }
    changes.setUpdates(updates);

    QList<T__FolderChangeType> changesList;
    changesList << changes;
    folderChanges.setFolderChange(changesList);
    request.setFolderChanges(folderChanges);

    UpdateFolderJob *job = new UpdateFolderJob(d->connection->d_ptr->service);
    job->setRequest(request);

    return 0;// new Reply(new ReplyPrivate(job));
}

Reply *Folder::remove(DeleteType mode) const
{
    Q_D(const Folder);
    return d->connection->deleteFolders(QList<Folder>() << *this, mode);
}

FolderPrivate::FolderPrivate()
{

}

FolderPrivate::FolderPrivate(const T__FolderType &value) :
    folder(value)
{
    EffectiveRightsPrivate *priv = new EffectiveRightsPrivate(value.effectiveRights());
    effectiveRights = EffectiveRights(*priv);

    QList<T__PermissionType> permissionList = value.permissionSet().permissions().permission();
    foreach (const T__PermissionType &permission, permissionList) {
        permissions << Permission(new PermissionPrivate(permission));
    }
}

FolderPrivate::FolderPrivate(const FolderPrivate &copy) :
    QSharedData(copy)
{

}
