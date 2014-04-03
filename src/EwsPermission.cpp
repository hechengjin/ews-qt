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

EwsPermission::EwsPermission() :
    d_ptr(0)
{

}

EwsPermission::EwsPermission(EwsPermissionPrivate *priv) :
    d_ptr(priv)
{
}

QString EwsPermission::userId() const
{
    Q_D(const EwsPermission);
    return d->permission.userId().sID();
}

bool EwsPermission::canCreateItems() const
{
    Q_D(const EwsPermission);
    return d->permission.canCreateItems();
}

bool EwsPermission::canCreateSubFolders() const
{
    Q_D(const EwsPermission);
    return d->permission.canCreateSubFolders();
}

bool EwsPermission::isFolderOwner() const
{
    Q_D(const EwsPermission);
    return d->permission.isFolderOwner();
}

bool EwsPermission::isFolderVisible() const
{
    Q_D(const EwsPermission);
    return d->permission.isFolderVisible();
}

bool EwsPermission::isFolderContact() const
{
    Q_D(const EwsPermission);
    return d->permission.isFolderContact();
}

QString EwsPermission::editItems() const
{
    Q_D(const EwsPermission);
    return m_editItems;
}

QString EwsPermission::deleteItems() const
{
    return m_deleteItems;
}

QString EwsPermission::readItems() const
{
    Q_D(const EwsPermission);
    return m_readItems;
}

QString EwsPermission::permissionLevel() const
{
    Q_D(const EwsPermission);
//    return d->permission.permissionLevel();;
}


EwsPermissionPrivate::EwsPermissionPrivate(const T__PermissionType &permissionType) :
    permission(permissionType)
{

}
