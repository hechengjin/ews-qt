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

#ifndef EWSSYNCFOLDERITEMSREPLY_P_H
#define EWSSYNCFOLDERITEMSREPLY_P_H

#include <QObject>

#include "reply_p.h"
#include "syncfolderitemsreply.h"
#include "wsdl_Services.h"

namespace Ews {

class SyncFolderItemsReplyPrivate : public ReplyPrivate
{
    Q_OBJECT
public:
    SyncFolderItemsReplyPrivate(KDSoapJob *job);

    void processJob(KDSoapJob *job);

    QString messageText;
    QString responseCode;
    QString syncState;
    bool includesLastItemInRange;
    QStringList deleteItems;

};

}

#endif // EWSSYNCFOLDERITEMSREPLY_P_H
