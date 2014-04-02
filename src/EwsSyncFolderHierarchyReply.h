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

#ifndef EWSSYNCFOLDERHIERARCHYREPLY_H
#define EWSSYNCFOLDERHIERARCHYREPLY_H

#include "ewsexport.h"
#include "EwsFolder.h"

#include <QStringList>

class EwsSyncFolderHierarchyReplyPrivate;
class EWS_EXPORT EwsSyncFolderHierarchyReply : public QObject
{
    Q_OBJECT
public:
    EwsSyncFolderHierarchyReply(QObject *exchangeServices);

    QString responseCode() const;
    QString syncState() const;
    bool includesLastFolderInRange() const;
    QList<EwsFolder> createFolders() const;
    QList<EwsFolder> updateFolders() const;
    /**
     * @brief deleteFolders is not empty when some folder
     * was permanetly deleted on the server
     * @return returns a list of IDs to be deleted
     */
    QStringList deleteFolders() const;

private:
    Q_DECLARE_PRIVATE(EwsSyncFolderHierarchyReply)
    EwsSyncFolderHierarchyReplyPrivate *d_ptr;
};

#endif // EWSSYNCFOLDERHIERARCHYREPLY_H
