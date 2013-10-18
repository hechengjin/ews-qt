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

#include "EwsConnection.h"

#include "EwsRequest.h"
#include "EwsAutoDiscoverReply.h"

#include "EwsSyncFolderHierarchyReply.h"
#include "EwsSyncFolderItemsReply.h"
#include "EwsUtils.h"

#include "ESoapNamespaces.h"

#include "wsdl_Services.h"

#include <QNetworkRequest>
#include <QSslConfiguration>
#include <QStringBuilder>
#include <QDebug>

EwsConnection::EwsConnection(QObject *parent, QNetworkAccessManager *networkAccessManager) :
    QObject(parent)
{
    if (networkAccessManager) {
        m_networkMgr = networkAccessManager;
    } else {
        m_networkMgr = new QNetworkAccessManager(this);
    }
    connect(m_networkMgr, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)),
            SLOT(sslErrors(QNetworkReply*,QList<QSslError>)));

    ESoapNamespaces::instance()->registerNamespace("t", EWS_TYPES_NS);
    ESoapNamespaces::instance()->registerNamespace("m", EWS_MESSAGES_NS);
    m_serverVersion = EwsRequest::Exchange2007_SP1;
}

EwsReply *EwsConnection::getFolders(const QList<EwsFolder> &folders, EwsFolder::BaseShape folderShape)
{
    EwsRequest message(QLatin1String("GetFolder"), m_serverVersion);

    ESoapElement folderShapeElement = message.createElement(QLatin1String("FolderShape"));
    message.method().appendChild(folderShapeElement);

    ESoapElement baseShape = message.createTypedElement(QLatin1String("BaseShape"), EWS_TYPES_NS);
    baseShape.setText(EwsUtils::enumToString<EwsFolder>("BaseShape", folderShape));
    folderShapeElement.appendChild(baseShape);

    appendFoldersIdsToElement(folders, message.method());

    return new EwsReply(post(message), message.methodName());
}

EwsReply *EwsConnection::deleteFolders(const QList<EwsFolder> &folders, EwsFolder::DeleteType mode)
{
    EwsRequest message(QLatin1String("DeleteFolder"), m_serverVersion);

    message.method().setAttribute(QLatin1String("DeleteType"),
                                  EwsUtils::enumToString<EwsFolder>("DeleteType", mode));

    appendFoldersIdsToElement(folders, message.method());

    return new EwsReply(post(message), message.methodName());
}

EwsSyncFolderHierarchyReply *EwsConnection::syncFolderHierarch(EwsFolder::BaseShape folderShape, const QString &folderId, const QString &syncState)
{
    TNS__SyncFolderHierarchyType request;

    T__DefaultShapeNamesType baseShape;
    baseShape.setType(T__DefaultShapeNamesType::AllProperties);
    T__FolderResponseShapeType shape;
    shape.setBaseShape(baseShape);
    request.setFolderShape(shape);

    if (!folderId.isEmpty()) {
        qDebug() << Q_FUNC_INFO << folderId;

        T__FolderIdType folderType;
        folderType.setId(folderId);

        T__TargetFolderIdType folder;
        folder.setFolderId(folderType);
        request.setSyncFolderId(folder);
    }

    if (!syncState.isEmpty()) {
        qDebug() << Q_FUNC_INFO << syncState;
        request.setSyncState(syncState);
    }

    ExchangeServices *service = new ExchangeServices;
    service->setEndPoint(m_uri.toString());
    T__ExchangeVersionType versionType(T__ExchangeVersionType::Exchange2007_SP1);
    T__RequestServerVersion version;
    version.setVersion(versionType);
    service->setRequestVersionHeader(version);
    service->asyncSyncFolderHierarchy(request);


//    EwsRequest message(QLatin1String("SyncFolderHierarchy"), m_serverVersion);

//    ESoapElement folderShapeElement = message.createElement(QLatin1String("FolderShape"));
//    message.method().appendChild(folderShapeElement);

//    ESoapElement baseShape = message.createTypedElement(QLatin1String("BaseShape"), EWS_TYPES_NS);
//    baseShape.setText(EwsUtils::enumToString<EwsFolder>("BaseShape", folderShape));
//    folderShapeElement.appendChild(baseShape);

//    if (!folderId.isEmpty()) {
//        ESoapElement syncFolderId = message.createElement(QLatin1String("SyncFolderId"));
//        message.method().appendChild(syncFolderId);
//        ESoapElement folderElement = message.createTypedElement(QLatin1String("FolderId"), EWS_TYPES_NS);
//        folderElement.setAttribute(QLatin1String("Id"), folderId);
//        syncFolderId.appendChild(folderElement);
//    }

//    if (!syncState.isEmpty()) {
//        ESoapElement syncElement = message.createElement(QLatin1String("SyncState"));
//        syncElement.setText(syncState);
//        message.method().appendChild(syncElement);
//    }

    return new EwsSyncFolderHierarchyReply(service);
}

EwsSyncFolderItemsReply *EwsConnection::syncFolderItems(EwsFolder::BaseShape itemShape, const QString &folderId, int maxChanges, const QString &syncState)
{
    EwsRequest message(QLatin1String("SyncFolderItems"), m_serverVersion);

    ESoapElement folderShape = message.createElement(QLatin1String("ItemShape"));
    message.method().appendChild(folderShape);

    ESoapElement baseShape = message.createTypedElement(QLatin1String("BaseShape"), EWS_TYPES_NS);
    baseShape.setText(EwsUtils::enumToString<EwsFolder>("BaseShape", itemShape));
    folderShape.appendChild(baseShape);

    ESoapElement syncFolderId = message.createElement(QLatin1String("SyncFolderId"));
    message.method().appendChild(syncFolderId);
    ESoapElement folderElement = message.createTypedElement(QLatin1String("FolderId"), EWS_TYPES_NS);
    folderElement.setAttribute(QLatin1String("Id"), folderId);
    syncFolderId.appendChild(folderElement);

    ESoapElement maxChangesElement = message.createElement(QLatin1String("MaxChangesReturned"));
    maxChangesElement.setText(QString::number(maxChanges));
    message.method().appendChild(maxChangesElement);

    if (!syncState.isEmpty()) {
        ESoapElement syncElement = message.createElement(QLatin1String("SyncState"));
        syncElement.setText(syncState);
        message.method().appendChild(syncElement);
    }

    return new EwsSyncFolderItemsReply(post(message));
}

void EwsConnection::setUri(const QUrl &uri)
{
    m_uri = uri;
}

EwsRequest::ServerVersion EwsConnection::serverVersion()
{
    return m_serverVersion;
}

QNetworkReply *EwsConnection::post(const EwsRequest &message)
{
    return postDocument(m_uri, message);
}

EwsAutoDiscoverReply *EwsConnection::post(const QUrl &url, const QDomDocument &document)
{
    qDebug() << Q_FUNC_INFO << url.toString(QUrl::PrettyDecoded);
    EwsAutoDiscoverReply *messageReply = new EwsAutoDiscoverReply(document, this);
    messageReply->setReply(postDocument(url, document));
    return messageReply;
}

EwsAutoDiscoverReply *EwsConnection::get(const QUrl &url, const QDomDocument &document)
{
    EwsAutoDiscoverReply *messageReply = new EwsAutoDiscoverReply(document, this);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QLatin1String("text/xml; charset=utf-8"));

    messageReply->setReply(m_networkMgr->get(request));
    return messageReply;
}

QNetworkReply *EwsConnection::postDocument(const QUrl &url, const QDomDocument &document)
{
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QLatin1String("text/xml; charset=utf-8"));

    return m_networkMgr->post(request, document.toString(-1).toUtf8().constData());
}

void EwsConnection::sslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
    qDebug() << Q_FUNC_INFO << reply->url().host();
    foreach (const QSslError &error, errors) {
        qDebug() << Q_FUNC_INFO << error.errorString();
    }
    reply->ignoreSslErrors();
}

void EwsConnection::appendFoldersIdsToElement(const QList<EwsFolder> &folders, ESoapElement element)
{
    EwsRequest request = static_cast<EwsRequest>(element.ownerDocument());
    ESoapElement folderIds = request.createElement(QLatin1String("FolderIds"));
    element.appendChild(folderIds);

    foreach (const EwsFolder &folder, folders) {
        ESoapElement folderIdElement;
        if (folder.id().isEmpty()) {
            folderIdElement = request.createTypedElement(QLatin1String("FolderId"), EWS_TYPES_NS);
            folderIdElement.setAttribute(QLatin1String("Id"), folder.id());
            if (!folder.changeKey().isEmpty()) {
                folderIdElement.setAttribute(QLatin1String("ChangeKey"), folder.changeKey());
            }
            folderIds.appendChild(folderIdElement);
        } else {
            folderIdElement = request.createTypedElement(QLatin1String("DistinguishedFolderId"), EWS_TYPES_NS);
            folderIdElement.setAttribute(QLatin1String("Id"), folder.wellKnownFolderNameString());
            if (!folder.changeKey().isEmpty()) {
                folderIdElement.setAttribute(QLatin1String("ChangeKey"), folder.changeKey());
            }
            folderIds.appendChild(folderIdElement);
        }
    }
}
