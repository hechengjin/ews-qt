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

#ifndef EWSSYNCFOLDERHIERARCHYREPLY_H
#define EWSSYNCFOLDERHIERARCHYREPLY_H

#include "export.h"
#include "folder.h"
#include "reply.h"

#include <QStringList>

namespace Ews {

class SyncFolderHierarchyReplyPrivate;
class EWS_EXPORT SyncFolderHierarchyReply : public Reply
{
    Q_OBJECT
public:
    SyncFolderHierarchyReply(SyncFolderHierarchyReplyPrivate *priv);

    QString responseCode() const;
    QString syncState() const;
    bool includesLastFolderInRange() const;
    QList<Folder> createFolders() const;
    QList<Folder> updateFolders() const;
    /**
     * @brief deleteFolders is not empty when some folder
     * was permanetly deleted on the server
     * @return returns a list of IDs to be deleted
     */
    QStringList deleteFolders() const;

private:
    Q_DECLARE_PRIVATE(SyncFolderHierarchyReply)
};

}

#endif // EWSSYNCFOLDERHIERARCHYREPLY_H
