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

#include "export.h"
#include "request.h"
#include "folder.h"

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QDomDocument>

namespace Ews {

class AutoDiscoverReply;
class Reply;
class SyncFolderItemsReply;
class SyncFolderHierarchyReply;
class ConnectionPrivate;
class EWS_EXPORT Connection : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Connection)
public:
    enum ServerVersion {
        Exchange2007,
        Exchange2007_SP1,
        Exchange2010,
        Exchange2010_SP1,
        Exchange2010_SP2
    };
    explicit Connection(QObject *parent = 0, QNetworkAccessManager *networkAccessManager = 0);
    ~Connection();

    Reply *getFolders(const QList<Folder> &folders, Folder::BaseShape folderShape);
    Reply *deleteFolders(const QList<Folder> &folders, Folder::DeleteType mode);
    SyncFolderHierarchyReply *syncFolderHierarch(Folder::BaseShape folderShape, const QString &folderId = QString(), const QString &syncState = QString());
    SyncFolderItemsReply *syncFolderItems(Folder::BaseShape itemShape, const QString &folderId, int maxChanges, const QString &syncState = QString());

    void setUri(const QUrl &uri);
    ServerVersion serverVersion() const;
    void setServerVersion(ServerVersion version);

    /**
     * Needed for autodiscover
     */
    AutoDiscoverReply *post(const QUrl &url, const QDomDocument &document);
    AutoDiscoverReply *get(const QUrl &url, const QDomDocument &document);

signals:
    void finished();

protected:
    /**
     * @brief POST a message to the given url
     * @param url where the message should be sent to (including username/password)
     * @param document the document to be sent
     * @return QNetworkReply is returned to keep track of the request.
     */
    QNetworkReply *postDocument(const QUrl &url, const QDomDocument &document);

    ConnectionPrivate *d_ptr;

private slots:
    void sslErrors(QNetworkReply *reply, const QList<QSslError> &errors);

private:
    friend class AutoDiscoverReply;
    friend class Folder;

    QNetworkAccessManager *m_networkMgr;
};

}

#endif // EWSCONNECTION_H
