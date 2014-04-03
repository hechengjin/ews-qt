/*
 * Copyright (C) 2013 Daniel Nicoletti <dantti12@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB. If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef EWSREPLY_P_H
#define EWSREPLY_P_H

#include <QObject>

#include "EwsReply.h"
#include "wsdl_Services.h"

namespace Ews {

class ReplyPrivate : public QObject
{
    Q_OBJECT
public:
    ReplyPrivate(KDSoapJob *job);

    QString messageText;
    QString responseCode;
    QString syncState;
    bool includesLastFolderInRange;

protected:
    /**
     * This is only called when the job
     * has finished without errors,
     *
     * DO NOT EMIT FINISHED
     */
    virtual void processJob(KDSoapJob *job);

signals:
    void finished();

private:
    void jobFinished(KDSoapJob *job);
};

}

#endif // EWSREPLY_P_H
