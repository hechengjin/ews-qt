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

#include "EwsFolder_p.h"

#include "EwsRequest.h"
#include "EwsConnection.h"
#include "EwsReply.h"
#include "EwsUtils.h"

#include <QMetaEnum>
#include <QStringBuilder>
#include <QDebug>

EwsFolder::EwsFolder(EwsConnection *connection, EwsFolder::WellKnownFolderName wellKnownFolderName, const QString &changeKey) :
    d_ptr(new EwsFolderPrivate)
{
    Q_D(EwsFolder);
    d->wellKnownFolderName = wellKnownFolderName;
    d->connection = connection;
//    d->folder.f
}

EwsFolder::EwsFolder(EwsConnection *connection, const QString &folderId, const QString &changeKey) :
    d_ptr(new EwsFolderPrivate)
{
    Q_D(EwsFolder);
//    d->wellKnownFolderName = wellKnownFolderName;
    d->connection = connection;
}

EwsFolder::EwsFolder() :
    d_ptr(new EwsFolderPrivate)
{
}

EwsFolder::~EwsFolder()
{
    delete d_ptr;
}

//EwsFolder::EwsFolder(const ESoapElement &rootElement) :
//    m_wellKnownFolderName(WellKnownFolderNameUnknown)
//{
//    ESoapElement element;

//    element = rootElement.firstChildElement();
//    while (!element.isNull()) {
//        if (element.equalNS(QLatin1String("FolderId"), EWS_TYPES_NS)) {
//            m_id = element.attribute(QLatin1String("Id"));
//            m_changeKey = element.attribute(QLatin1String("ChangeKey"));
//        } else if (element.equalNS(QLatin1String("ParentFolderId"), EWS_TYPES_NS)) {
//            m_parentId = element.attribute(QLatin1String("Id"));
//            m_parentChangeKey = element.attribute(QLatin1String("ChangeKey"));
//        } else if (element.equalNS(QLatin1String("FolderClass"), EWS_TYPES_NS)) {
//            m_folderClass = element.text();
//        } else if (element.equalNS(QLatin1String("DisplayName"), EWS_TYPES_NS)) {
//            m_displayName = element.text();
//        } else if (element.equalNS(QLatin1String("TotalCount"), EWS_TYPES_NS)) {
//            m_totalCount = element.text().toInt();
//        } else if (element.equalNS(QLatin1String("ChildFolderCount"), EWS_TYPES_NS)) {
//            m_childFolderCount = element.text().toInt();
//        } else if (element.equalNS(QLatin1String("EffectiveRights"), EWS_TYPES_NS)) {
//            m_effectiveRights = EwsEffectiveRights(element);
//        } else if (element.equalNS(QLatin1String("UnreadCount"), EWS_TYPES_NS)) {
//            m_unreadCount = element.text().toInt();
//        } else if (element.equalNS(QLatin1String("PermissionSet"), EWS_TYPES_NS)) {
//            ESoapElement permissions = element.firstChildTypedElement(QLatin1String("Permissions"), EWS_TYPES_NS);
//            ESoapElement permission = permissions.firstChildTypedElement(QLatin1String("Permission"), EWS_TYPES_NS);
//            while (!permission.isNull()) {
//                m_permissions << EwsPermission(permission);

//                permission = permission.nextSiblingElement();
//            }
//        } else {
//            qWarning() << Q_FUNC_INFO << "element unknown" << element.nodeName();
//        }

//        element = element.nextSiblingElement();
//    }
//}

QString EwsFolder::id() const
{
    Q_D(const EwsFolder);
//    return d->folder.folderId().id();
}

void EwsFolder::setId(const QString &id)
{
//    m_id = id;
}

QString EwsFolder::changeKey() const
{
    Q_D(const EwsFolder);
//    return d->folder.folderId().changeKey();
}

void EwsFolder::setChangeKey(const QString &changeKey)
{
//    m_changeKey = changeKey;
}

EwsFolder::WellKnownFolderName EwsFolder::wellKnownFolderName() const
{
    Q_D(const EwsFolder);
    return d->wellKnownFolderName;
}

QString EwsFolder::wellKnownFolderNameString() const
{
    Q_D(const EwsFolder);
    return EwsUtils::enumToString<EwsFolder>("WellKnownFolderName", d->wellKnownFolderName).toLower();
}

QString EwsFolder::folderClass() const
{
    Q_D(const EwsFolder);
//    return d->folder.folderClass();
}

QString EwsFolder::parentId() const
{
    Q_D(const EwsFolder);
//    return d->folder.parentFolderId().id();
}

QString EwsFolder::parentChangeKey() const
{
    Q_D(const EwsFolder);
//    return d->folder.parentFolderId().changeKey();
}

QString EwsFolder::displayName() const
{
    Q_D(const EwsFolder);
//    return d->folder.displayName();
}

void EwsFolder::setDisplayName(const QString &displayName)
{
    Q_D(EwsFolder);
//    d->changes[QLatin1String("DisplayName")] = displayName;
}

EwsEffectiveRights EwsFolder::effectiveRights() const
{
    Q_D(const EwsFolder);
//    return d->folder.effectiveRights();
}

int EwsFolder::totalCount() const
{
    Q_D(const EwsFolder);
    return d->folder.totalCount();
}

int EwsFolder::unreadCount() const
{
    Q_D(const EwsFolder);
    return d->folder.unreadCount();
}

int EwsFolder::childFolderCount() const
{
    Q_D(const EwsFolder);
    return d->folder.childFolderCount();
}

QList<EwsPermission> EwsFolder::permissions() const
{
    Q_D(const EwsFolder);
    return d->permissions;
}

EwsReply *EwsFolder::load(BaseShape folderShape) const
{
    Q_D(const EwsFolder);
    return d->connection->getFolders(QList<EwsFolder>() << *this, folderShape);
}

EwsReply *EwsFolder::update() const
{
    Q_D(const EwsFolder);


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

    ExchangeServices *service = new ExchangeServices;
//    service->setEndPoint(m_uri.toString());
    T__ExchangeVersionType versionType(T__ExchangeVersionType::Exchange2007_SP1);
    T__RequestServerVersion version;
    version.setVersion(versionType);
    service->setRequestVersionHeader(version);
    service->asyncUpdateFolder(request);

    return new EwsReply(service);

//    EwsRequest message(QLatin1String("UpdateFolder"), m_connection->serverVersion());
//    ESoapElement folderChanges = message.createElement(QLatin1String("FolderChanges"));
//    message.method().appendChild(folderChanges);

//    QHash<QString, QString>::ConstIterator i = d->changes.begin();
//    while (i != d->changes.end()) {
//        ESoapElement folderChange = message.createTypedElement(QLatin1String("FolderChange"), EWS_TYPES_NS);
//        folderChanges.appendChild(folderChange);

//        ESoapElement folderIdElement = message.createTypedElement(QLatin1String("FolderId"), EWS_TYPES_NS);
////        folderIdElement.setAttribute(QLatin1String("Id"), d->id);
////        if (!d->changeKey.isEmpty()) {
////            folderIdElement.setAttribute(QLatin1String("ChangeKey"), d->changeKey);
////        }
//        folderChange.appendChild(folderIdElement);

//        ESoapElement updates = message.createTypedElement(QLatin1String("Updates"), EWS_TYPES_NS);
//        folderChange.appendChild(updates);

//        ESoapElement setFolderField = message.createTypedElement(QLatin1String("SetFolderField"), EWS_TYPES_NS);
//        updates.appendChild(setFolderField);

//        ESoapElement fieldURI = message.createTypedElement(QLatin1String("FieldURI"), EWS_TYPES_NS);
//        fieldURI.setAttribute(QLatin1String("FieldURI"), QLatin1String("folder:") % i.key());
//        setFolderField.appendChild(fieldURI);

//        ESoapElement folderElement = message.createTypedElement(QLatin1String("Folder"), EWS_TYPES_NS);
//        setFolderField.appendChild(folderElement);

//        ESoapElement itemChanged = message.createTypedElement(i.key(), EWS_TYPES_NS);
//        itemChanged.setText(i.value());
//        folderElement.appendChild(itemChanged);

//        ++i;
//    }

//    return new EwsReply(d->connection->post(message), message.methodName());
}

EwsReply *EwsFolder::remove(DeleteType mode) const
{
    Q_D(const EwsFolder);
    return d->connection->deleteFolders(QList<EwsFolder>() << *this, mode);
}

#include "moc_EwsFolder.cpp"

void EwsFolderPrivate::setData(const T__FolderType &value)
{
    folder = value;
    folder.permissionSet();
}

EwsFolderPrivate::~EwsFolderPrivate()
{

}
