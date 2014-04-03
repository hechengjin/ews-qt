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

#include "reply_p.h"
#include "connection.h"
#include "utils.h"

#include "wsdl_Services.h"

#include <QStringBuilder>
#include <QDebug>

using namespace Ews;

Reply::Reply(void *job) :
    d_ptr(new ReplyPrivate(static_cast<KDSoapJob *>(job)))
{
    Q_D(Reply);
    connect(d, &ReplyPrivate::finished,
            this, &Reply::finished);
}

Reply::~Reply()
{
    delete d_ptr;
}

bool Reply::error() const
{
    Q_D(const Reply);
    return !d->responseCode.isEmpty();
}

Reply::ResponseCode Reply::responseCode() const
{
    Q_D(const Reply);
    return NoError;
}

QString Reply::errorMessage() const
{
    Q_D(const Reply);
    return d->responseCode;
}

ReplyPrivate::ReplyPrivate(KDSoapJob *job)
{
    connect(job, &KDSoapJob::finished,
            this, &ReplyPrivate::jobFinished);
    job->start();
}

void ReplyPrivate::processJob(KDSoapJob *job)
{
    // TODO make this pure virtual
}

void ReplyPrivate::jobFinished(KDSoapJob *job)
{
    if (job->isFault()) {
        responseCode = job->faultAsString();
    } else {
        // Tell the specialization to
        // do their job
        processJob(job);
    }
    emit finished();
}
