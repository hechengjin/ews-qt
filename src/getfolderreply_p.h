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

#ifndef EWSGETFOLDERREPLY_P_H
#define EWSGETFOLDERREPLY_P_H

#include <QObject>

#include "wsdl_Services.h"

#include "reply_p.h"
#include "getfolderreply.h"
#include "folder_p.h"

namespace Ews {

class GetFolderReplyPrivate : public ReplyPrivate
{
    Q_OBJECT
public:
    GetFolderReplyPrivate(KDSoapJob *job);

    void processJob(KDSoapJob *job);

    QList<Folder> foldersList;
};

}

#endif // EWSGETFOLDERREPLY_P_H
