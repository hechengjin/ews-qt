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

Folder::Folder(Connection *connection, Folder::WellKnownFolderName wellKnownFolderName, const QString &changeKey)
    : d_ptr(new FolderPrivate)
{
    Q_D(Folder);
    d->wellKnownFolderName = wellKnownFolderName;
    d->connection = connection;
//    d->folder.f
}

Folder::Folder(Connection *connection, const QString &folderId, const QString &changeKey)
    : d_ptr(new FolderPrivate)
{
    Q_D(Folder);
//    d->wellKnownFolderName = wellKnownFolderName;
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

//Folder::Folder(const ESoapElement &rootElement) :
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

QString Folder::id() const
{
    Q_D(const Folder);
    return d->folder.folderId().id();
}

void Folder::setId(const QString &id)
{
//    m_id = id;
}

QString Folder::changeKey() const
{
    Q_D(const Folder);
    return d->folder.folderId().changeKey();
}

void Folder::setChangeKey(const QString &changeKey)
{
//    m_changeKey = changeKey;
}

Folder::WellKnownFolderName Folder::wellKnownFolderName() const
{
    Q_D(const Folder);
    return d->wellKnownFolderName;
}

QString Folder::wellKnownFolderNameString() const
{
    Q_D(const Folder);
    return d->folder.folderClass();
//    return EwsUtils::enumToString<Folder>("WellKnownFolderName", d->wellKnownFolderName).toLower();
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
//    Q_D(Folder);
//    d->changes[QLatin1String("DisplayName")] = displayName;
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

Reply *Folder::load(BaseShape folderShape) const
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

    return new Reply(new ReplyPrivate(job));

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
    effectiveRights = EffectiveRights(new EffectiveRightsPrivate(value.effectiveRights()));

    QList<T__PermissionType> permissionList = value.permissionSet().permissions().permission();
    foreach (const T__PermissionType &permission, permissionList) {
        permissions << Permission(new PermissionPrivate(permission));
    }
}

FolderPrivate::FolderPrivate(const FolderPrivate &copy) :
    QSharedData(copy)
{

}
