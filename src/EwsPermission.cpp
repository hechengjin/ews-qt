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

#include "EwsPermission.h"
#include "EwsRequest.h"

#include <QDebug>

EwsPermission::EwsPermission()
{
//    ESoapElement element;;

//    element = rootElement.firstChildElement();
//    while (!element.isNull()) {
//        if (element.equalNS(QLatin1String("UserId"), EWS_TYPES_NS)) {
//            m_userId = element.text();
//        } else if (element.equalNS(QLatin1String("CanCreateItems"), EWS_TYPES_NS)) {
//            m_canCreateItems = element.text() == QLatin1String("true");
//        } else if (element.equalNS(QLatin1String("CanCreateSubFolders"), EWS_TYPES_NS)) {
//            m_canCreateSubFolders = element.text() == QLatin1String("true");
//        } else if (element.equalNS(QLatin1String("IsFolderOwner"), EWS_TYPES_NS)) {
//            m_isFolderOwner = element.text() == QLatin1String("true");
//        } else if (element.equalNS(QLatin1String("IsFolderVisible"), EWS_TYPES_NS)) {
//            m_isFolderVisible = element.text() == QLatin1String("true");
//        } else if (element.equalNS(QLatin1String("IsFolderContact"), EWS_TYPES_NS)) {
//            m_isFolderContact = element.text() == QLatin1String("true");
//        } else if (element.equalNS(QLatin1String("EditItems"), EWS_TYPES_NS)) {
//            m_editItems = element.text() == QLatin1String("true");
//        } else if (element.equalNS(QLatin1String("DeleteItems"), EWS_TYPES_NS)) {
//            m_deleteItems = element.text() == QLatin1String("true");
//        } else if (element.equalNS(QLatin1String("ReadItems"), EWS_TYPES_NS)) {
//            m_readItems = element.text();
//        } else if (element.equalNS(QLatin1String("PermissionLevel"), EWS_TYPES_NS)) {
//            m_permissionLevel = element.text();
//        } else {
//            // TODO create PermissionSet class
//            qWarning() << Q_FUNC_INFO << "element unknown" << element.nodeName();
//        }

//        element = element.nextSiblingElement();
//    }
}

QString EwsPermission::userId() const
{
    return m_userId;
}

bool EwsPermission::canCreateItems() const
{
    return m_canCreateItems;
}

bool EwsPermission::canCreateSubFolders() const
{
    return m_canCreateSubFolders;
}

bool EwsPermission::isFolderOwner() const
{
    return m_isFolderOwner;
}

bool EwsPermission::isFolderVisible() const
{
    return m_isFolderVisible;
}

bool EwsPermission::isFolderContact() const
{
    return m_isFolderContact;
}

QString EwsPermission::editItems() const
{
    return m_editItems;
}

QString EwsPermission::deleteItems() const
{
    return m_deleteItems;
}

QString EwsPermission::readItems() const
{
    return m_readItems;
}

QString EwsPermission::permissionLevel() const
{
    return m_permissionLevel;
}
