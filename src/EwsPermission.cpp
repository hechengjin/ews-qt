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

#include "EwsPermission_p.h"
#include "EwsRequest.h"

#include <QDebug>

using namespace Ews;

Permission::Permission() :
    d_ptr(0)
{
}

Permission::Permission(PermissionPrivate *priv) :
    d_ptr(priv)
{
}

QString Permission::userId() const
{
    Q_D(const Permission);
    return d->permission.userId().sID();
}

bool Permission::canCreateItems() const
{
    Q_D(const Permission);
    return d->permission.canCreateItems();
}

bool Permission::canCreateSubFolders() const
{
    Q_D(const Permission);
    return d->permission.canCreateSubFolders();
}

bool Permission::isFolderOwner() const
{
    Q_D(const Permission);
    return d->permission.isFolderOwner();
}

bool Permission::isFolderVisible() const
{
    Q_D(const Permission);
    return d->permission.isFolderVisible();
}

bool Permission::isFolderContact() const
{
    Q_D(const Permission);
    return d->permission.isFolderContact();
}

QString Permission::editItems() const
{
    Q_D(const Permission);
    return m_editItems;
}

QString Permission::deleteItems() const
{
    return m_deleteItems;
}

QString Permission::readItems() const
{
    Q_D(const Permission);
    return m_readItems;
}

QString Permission::permissionLevel() const
{
    Q_D(const Permission);
//    return d->permission.permissionLevel();;
}


PermissionPrivate::PermissionPrivate(const T__PermissionType &permissionType) :
    permission(permissionType)
{

}
