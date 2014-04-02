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

#ifndef EWSCONNECTION_H
#define EWSCONNECTION_H

#include "ewsexport.h"
#include "EwsRequest.h"
#include "EwsFolder.h"

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QDomDocument>

class EwsAutoDiscoverReply;
class EwsReply;
class EwsSyncFolderItemsReply;
class EwsSyncFolderHierarchyReply;
class EwsConnectionPrivate;
class EWS_EXPORT EwsConnection : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(EwsConnection)
public:
    enum ServerVersion {
        Exchange2007,
        Exchange2007_SP1,
        Exchange2010,
        Exchange2010_SP1,
        Exchange2010_SP2
    };
    explicit EwsConnection(QObject *parent = 0, QNetworkAccessManager *networkAccessManager = 0);
    ~EwsConnection();

    EwsReply *getFolders(const QList<EwsFolder> &folders, EwsFolder::BaseShape folderShape);
    EwsReply *deleteFolders(const QList<EwsFolder> &folders, EwsFolder::DeleteType mode);
    EwsSyncFolderHierarchyReply *syncFolderHierarch(EwsFolder::BaseShape folderShape, const QString &folderId = QString(), const QString &syncState = QString());
    EwsSyncFolderItemsReply *syncFolderItems(EwsFolder::BaseShape itemShape, const QString &folderId, int maxChanges, const QString &syncState = QString());

    void setUri(const QUrl &uri);
    ServerVersion serverVersion() const;
    void setServerVersion(ServerVersion version);

    /**
     * Needed for autodiscover
     */
    EwsAutoDiscoverReply *post(const QUrl &url, const QDomDocument &document);
    EwsAutoDiscoverReply *get(const QUrl &url, const QDomDocument &document);

signals:
    void finished();

protected:
    /**
     * @brief POST a message to the give url
     * @param url where the message should be sent to (including username/password)
     * @param document the document to be sent
     * @return QNetworkReply is returned to keep track of the request.
     */
    QNetworkReply *postDocument(const QUrl &url, const QDomDocument &document);

    EwsConnectionPrivate *d_ptr;

private slots:
    void sslErrors(QNetworkReply *reply, const QList<QSslError> &errors);

private:
    friend class EwsAutoDiscoverReply;

    QNetworkAccessManager *m_networkMgr;
};

#endif // EWSCONNECTION_H
