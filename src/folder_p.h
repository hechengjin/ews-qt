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

#ifndef EWSFOLDER_P_H
#define EWSFOLDER_P_H

#include "folder.h"

#include "wsdl_Services.h"

namespace Ews {

class FolderPrivate : public QSharedData
{
public:
    explicit FolderPrivate();
    explicit FolderPrivate(const T__FolderType &value);
    explicit FolderPrivate(const FolderPrivate &copy);

    T__FolderType folder;
    Folder::WellKnownFolderName wellKnownFolderName;
    EffectiveRights effectiveRights;
    QList<Permission> permissions;
    QHash<QString, QString> changes;
    Connection *connection;
};

}

#endif // EWSFOLDER_P_H
