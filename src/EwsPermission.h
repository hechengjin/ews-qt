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

#ifndef EWSPERMISSION_H
#define EWSPERMISSION_H

#include "ewsexport.h"

#include <QObject>
#include <QString>

class EwsPermissionPrivate;
class EWS_EXPORT EwsPermission
{
    Q_GADGET
    Q_DECLARE_PRIVATE(EwsPermission)
public:
    EwsPermission();
    EwsPermission(EwsPermissionPrivate *priv);

    QString userId() const;
    bool canCreateItems() const;
    bool canCreateSubFolders() const;
    bool isFolderOwner() const;
    bool isFolderVisible() const;
    bool isFolderContact() const;
    QString editItems() const;
    QString deleteItems() const;

    QString readItems() const;
    QString permissionLevel() const;

private:
    EwsPermissionPrivate *d_ptr;
    QString m_userId;
    bool m_canCreateItems;
    bool m_canCreateSubFolders;
    bool m_isFolderOwner;
    bool m_isFolderVisible;
    bool m_isFolderContact;
    QString m_editItems;
    QString m_deleteItems;

    QString m_readItems;
    QString m_permissionLevel;
};

#endif // EWSPERMISSION_H
