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

#ifndef EWSSYNCFOLDERITEMSREPLY_H
#define EWSSYNCFOLDERITEMSREPLY_H

#include "ewsexport.h"
#include "EwsMessage.h"

class EwsSyncFolderItemsReplyPrivate;
class EWS_EXPORT EwsSyncFolderItemsReply : public QObject
{
    Q_OBJECT
public:
    QString responseCode() const;
    QString syncState() const;
    bool includesLastItemInRange() const;
    QList<EwsMessage> createMessages() const;

protected:
    EwsSyncFolderItemsReply(QObject *reply);

private:
    QString m_messageText;
    QString m_responseCode;
    QString m_syncState;
    bool m_includesLastItemInRange;
    QList<EwsMessage> m_createMessages;

private:
    friend class EwsConnection;
    Q_DECLARE_PRIVATE(EwsSyncFolderItemsReply)
    EwsSyncFolderItemsReplyPrivate *d_ptr;
};

#endif // EWSSYNCFOLDERITEMSREPLY_H
