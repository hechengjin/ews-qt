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

#include "EwsFolder.h"

#include "EwsRequest.h"
#include "EwsConnection.h"
#include "EwsReply.h"
#include "EwsUtils.h"

#include <QMetaEnum>
#include <QStringBuilder>
#include <QDebug>

EwsFolder::EwsFolder(EwsConnection *connection, EwsFolder::WellKnownFolderName wellKnownFolderName, const QString &changeKey) :
    m_wellKnownFolderName(wellKnownFolderName),
    m_changeKey(changeKey),
    m_connection(connection)
{
}

EwsFolder::EwsFolder(EwsConnection *connection, const QString &folderId, const QString &changeKey) :
    m_id(folderId),
    m_changeKey(changeKey),
    m_connection(connection)
{
}

EwsFolder::EwsFolder(const ESoapElement &rootElement) :
    m_wellKnownFolderName(WellKnownFolderNameUnknown)
{
    ESoapElement element;

    element = rootElement.firstChildElement();
    while (!element.isNull()) {
        if (element.equalNS(QLatin1String("FolderId"), EWS_TYPES_NS)) {
            m_id = element.attribute(QLatin1String("Id"));
            m_changeKey = element.attribute(QLatin1String("ChangeKey"));
        } else if (element.equalNS(QLatin1String("ParentFolderId"), EWS_TYPES_NS)) {
            m_parentId = element.attribute(QLatin1String("Id"));
            m_parentChangeKey = element.attribute(QLatin1String("ChangeKey"));
        } else if (element.equalNS(QLatin1String("FolderClass"), EWS_TYPES_NS)) {
            m_folderClass = element.text();
        } else if (element.equalNS(QLatin1String("DisplayName"), EWS_TYPES_NS)) {
            m_displayName = element.text();
        } else if (element.equalNS(QLatin1String("TotalCount"), EWS_TYPES_NS)) {
            m_totalCount = element.text().toInt();
        } else if (element.equalNS(QLatin1String("ChildFolderCount"), EWS_TYPES_NS)) {
            m_childFolderCount = element.text().toInt();
        } else if (element.equalNS(QLatin1String("EffectiveRights"), EWS_TYPES_NS)) {
            m_effectiveRights = EwsEffectiveRights(element);
        } else if (element.equalNS(QLatin1String("UnreadCount"), EWS_TYPES_NS)) {
            m_unreadCount = element.text().toInt();
        } else if (element.equalNS(QLatin1String("PermissionSet"), EWS_TYPES_NS)) {
            ESoapElement permissions = element.firstChildTypedElement(QLatin1String("Permissions"), EWS_TYPES_NS);
            ESoapElement permission = permissions.firstChildTypedElement(QLatin1String("Permission"), EWS_TYPES_NS);
            while (!permission.isNull()) {
                m_permissions << EwsPermission(permission);

                permission = permission.nextSiblingElement();
            }
        } else {
            qWarning() << Q_FUNC_INFO << "element unknown" << element.nodeName();
        }

        element = element.nextSiblingElement();
    }
}

QString EwsFolder::id() const
{
    return m_id;
}

QString EwsFolder::changeKey() const
{
    return m_changeKey;
}

EwsFolder::WellKnownFolderName EwsFolder::wellKnownFolderName() const
{
    return m_wellKnownFolderName;
}

QString EwsFolder::wellKnownFolderNameString() const
{
    return EwsUtils::enumToString<EwsFolder>("WellKnownFolderName", m_wellKnownFolderName).toLower();
}

QString EwsFolder::folderClass() const
{
    return m_folderClass;
}

QString EwsFolder::parentId() const
{
    return m_parentId;
}

QString EwsFolder::parentChangeKey() const
{
    return m_parentChangeKey;
}

QString EwsFolder::displayName() const
{
    return m_displayName;
}

void EwsFolder::setDisplayName(const QString &displayName)
{
    m_changes[QLatin1String("DisplayName")] = displayName;
}

EwsEffectiveRights EwsFolder::effectiveRights() const
{
    return m_effectiveRights;
}

int EwsFolder::totalCount() const
{
    return m_totalCount;
}

int EwsFolder::unreadCount() const
{
    return m_unreadCount;
}

int EwsFolder::childFolderCount() const
{
    return m_childFolderCount;
}

QList<EwsPermission> EwsFolder::permissions() const
{
    return m_permissions;
}

EwsReply *EwsFolder::load(BaseShape folderShape) const
{
    return m_connection->getFolders(QList<EwsFolder>() << *this, folderShape);
}

EwsReply *EwsFolder::update() const
{
    EwsRequest message(QLatin1String("UpdateFolder"), m_connection->serverVersion());
    ESoapElement folderChanges = message.createElement(QLatin1String("FolderChanges"));
    message.method().appendChild(folderChanges);

    QHash<QString, QString>::ConstIterator i = m_changes.begin();
    while (i != m_changes.end()) {
        ESoapElement folderChange = message.createTypedElement(QLatin1String("FolderChange"), EWS_TYPES_NS);
        folderChanges.appendChild(folderChange);

        ESoapElement folderIdElement = message.createTypedElement(QLatin1String("FolderId"), EWS_TYPES_NS);
        folderIdElement.setAttribute(QLatin1String("Id"), m_id);
        if (!m_changeKey.isEmpty()) {
            folderIdElement.setAttribute(QLatin1String("ChangeKey"), m_changeKey);
        }
        folderChange.appendChild(folderIdElement);

        ESoapElement updates = message.createTypedElement(QLatin1String("Updates"), EWS_TYPES_NS);
        folderChange.appendChild(updates);

        ESoapElement setFolderField = message.createTypedElement(QLatin1String("SetFolderField"), EWS_TYPES_NS);
        updates.appendChild(setFolderField);

        ESoapElement fieldURI = message.createTypedElement(QLatin1String("FieldURI"), EWS_TYPES_NS);
        fieldURI.setAttribute(QLatin1String("FieldURI"), QLatin1String("folder:") % i.key());
        setFolderField.appendChild(fieldURI);

        ESoapElement folderElement = message.createTypedElement(QLatin1String("Folder"), EWS_TYPES_NS);
        setFolderField.appendChild(folderElement);

        ESoapElement itemChanged = message.createTypedElement(i.key(), EWS_TYPES_NS);
        itemChanged.setText(i.value());
        folderElement.appendChild(itemChanged);

        ++i;
    }

    return new EwsReply(m_connection->post(message), message.methodName());
}

EwsReply *EwsFolder::remove(DeleteType mode) const
{
    return m_connection->deleteFolders(QList<EwsFolder>() << *this, mode);
}

#include "moc_EwsFolder.cpp"
