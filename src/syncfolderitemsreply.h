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

#ifndef EWSSYNCFOLDERITEMSREPLY_H
#define EWSSYNCFOLDERITEMSREPLY_H

#include "export.h"
#include "reply.h"

namespace Ews {

class SyncFolderItemsReplyPrivate;
class EWS_EXPORT SyncFolderItemsReply : public Reply
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(SyncFolderItemsReply)
public:
    QString responseCode() const;
    QString syncState() const;
    bool includesLastItemInRange() const;

protected:
    SyncFolderItemsReply(SyncFolderItemsReplyPrivate *priv);

private:
    friend class Connection;
    SyncFolderItemsReplyPrivate *d_ptr;
};

}

#endif // EWSSYNCFOLDERITEMSREPLY_H
