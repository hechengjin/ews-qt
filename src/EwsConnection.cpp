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

#include "EwsConnection_p.h"

#include "EwsRequest.h"
#include "EwsReply.h"
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
    QObject(parent),
    d_ptr(new EwsConnectionPrivate)
{
    Q_D(EwsConnection);

    d->service = new ExchangeServices(this);
    if (networkAccessManager) {
        m_networkMgr = networkAccessManager;
    } else {
        m_networkMgr = new QNetworkAccessManager(this);
    }
    connect(m_networkMgr, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)),
            SLOT(sslErrors(QNetworkReply*,QList<QSslError>)));

//    ESoapNamespaces::instance()->registerNamespace("t", EWS_TYPES_NS);
//    ESoapNamespaces::instance()->registerNamespace("m", EWS_MESSAGES_NS);
    setServerVersion(EwsRequest::Exchange2007);
}

EwsConnection::~EwsConnection()
{
    delete d_ptr;
}

EwsReply *EwsConnection::getFolders(const QList<EwsFolder> &folders, EwsFolder::BaseShape folderShape)
{
    Q_D(EwsConnection);

    TNS__GetFolderType request;

    T__NonEmptyArrayOfBaseFolderIdsType baseFolderIds;
    QList<T__FolderIdType> folderIds;
    foreach (const EwsFolder &folder, folders) {
        T__FolderIdType folderId;
        folderId.setId(folder.id());
        folderId.setChangeKey(folder.changeKey());
        folderIds << folderId;
    }
    baseFolderIds.setFolderId(folderIds);
    request.setFolderIds(baseFolderIds);

    GetFolderJob *job = new GetFolderJob(d->service, this);
    job->setRequest(request);
    job->start();

    return new EwsReply(job);
}

EwsReply *EwsConnection::deleteFolders(const QList<EwsFolder> &folders, EwsFolder::DeleteType mode)
{
    Q_D(EwsConnection);

    TNS__DeleteFolderType request;

    T__DisposalType deleteMode;
    switch (mode) {
    case EwsFolder::HardDelete:
        deleteMode.setType(T__DisposalType::HardDelete);
        break;
    case EwsFolder::MoveToDeletedItems:
        deleteMode.setType(T__DisposalType::MoveToDeletedItems);
        break;
    case EwsFolder::SoftDelete:
        deleteMode.setType(T__DisposalType::SoftDelete);
        break;
    }
    request.setDeleteType(deleteMode);

    T__NonEmptyArrayOfBaseFolderIdsType baseFolderIds;
    QList<T__FolderIdType> folderIds;
    foreach (const EwsFolder &folder, folders) {
        T__FolderIdType folderId;
        folderId.setId(folder.id());
        folderId.setChangeKey(folder.changeKey());
        folderIds << folderId;
    }
    baseFolderIds.setFolderId(folderIds);
    request.setFolderIds(baseFolderIds);

    DeleteFolderJob *job = new DeleteFolderJob(d->service, this);
    job->setRequest(request);
    job->start();

    return new EwsReply(job);
}

EwsSyncFolderHierarchyReply *EwsConnection::syncFolderHierarch(EwsFolder::BaseShape folderShape, const QString &folderId, const QString &syncState)
{
    Q_D(EwsConnection);

    TNS__SyncFolderHierarchyType request;

    T__DefaultShapeNamesType baseShape;
    baseShape.setType(T__DefaultShapeNamesType::AllProperties);
    T__FolderResponseShapeType shape;
    shape.setBaseShape(baseShape);
    request.setFolderShape(shape);

    if (!folderId.isEmpty()) {
        T__FolderIdType folderType;
        folderType.setId(folderId);

        T__TargetFolderIdType folder;
        folder.setFolderId(folderType);
        request.setSyncFolderId(folder);
    }

    if (!syncState.isEmpty()) {
        request.setSyncState(syncState);
    }

    SyncFolderHierarchyJob *job = new SyncFolderHierarchyJob(d->service, this);
    job->setRequest(request);
    job->start();

    return new EwsSyncFolderHierarchyReply(job);
}

EwsSyncFolderItemsReply *EwsConnection::syncFolderItems(EwsFolder::BaseShape itemShape, const QString &folderId, int maxChanges, const QString &syncState)
{
    Q_D(EwsConnection);

    TNS__SyncFolderItemsType request;

    T__DefaultShapeNamesType baseShape;
    baseShape.setType(T__DefaultShapeNamesType::AllProperties);
    T__ItemResponseShapeType shape;
    shape.setBaseShape(baseShape);
    request.setItemShape(shape);

    if (!folderId.isEmpty()) {
        T__FolderIdType folderType;
        folderType.setId(folderId);

        T__TargetFolderIdType folder;
        folder.setFolderId(folderType);
        request.setSyncFolderId(folder);
    }

    if (!syncState.isEmpty()) {
        request.setSyncState(syncState);
    }

    T__MaxSyncChangesReturnedType maxSyncChanges;
    maxSyncChanges.setValue(maxChanges);
    request.setMaxChangesReturned(maxSyncChanges);

    SyncFolderItemsJob *job = new SyncFolderItemsJob(d->service, this);
    job->setRequest(request);
    job->start();

    return new EwsSyncFolderItemsReply(job);
}

void EwsConnection::setUri(const QUrl &uri)
{
    Q_D(EwsConnection);
    d->uri = uri;
    d->service->setEndPoint(uri.toString());
}

EwsRequest::ServerVersion EwsConnection::serverVersion() const
{
    Q_D(const EwsConnection);
    return d->serverVersion;
}

void EwsConnection::setServerVersion(EwsRequest::ServerVersion ver)
{
    Q_D(EwsConnection);

    d->serverVersion = ver;
    T__RequestServerVersion version;
    switch (ver) {
    case EwsRequest::Exchange2007:
        version.setVersion(T__ExchangeVersionType(T__ExchangeVersionType::Exchange2007));
        break;
    case EwsRequest::Exchange2007_SP1:
        version.setVersion(T__ExchangeVersionType(T__ExchangeVersionType::Exchange2007_SP1));
        break;
    default:
        version.setVersion(T__ExchangeVersionType(T__ExchangeVersionType::Exchange2007_SP1));
    }

    d->service->setRequestVersionHeader(version);
}

QNetworkReply *EwsConnection::post(const EwsRequest &message)
{
    Q_D(EwsConnection);
    return postDocument(d->uri, message);
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
