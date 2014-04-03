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

#include "EwsReply_p.h"
#include "EwsConnection.h"
#include "EwsUtils.h"

#include "wsdl_Services.h"

#include <QStringBuilder>
#include <QDebug>

EwsReply::EwsReply(void *job) :
    d_ptr(new EwsReplyPrivate(static_cast<KDSoapJob *>(job)))
{
    Q_D(EwsReply);
    connect(d, &EwsReplyPrivate::finished,
            this, &EwsReply::finished);
}

EwsReply::~EwsReply()
{
    delete d_ptr;
}

bool EwsReply::error() const
{
    Q_D(const EwsReply);
    return !d->responseCode.isEmpty();
}

EwsReply::ResponseCode EwsReply::responseCode() const
{
    Q_D(const EwsReply);
    return NoError;
}

QString EwsReply::errorMessage() const
{
    Q_D(const EwsReply);
    return d->responseCode;
}

EwsReplyPrivate::EwsReplyPrivate(KDSoapJob *job)
{
    connect(job, &KDSoapJob::finished,
            this, &EwsReplyPrivate::jobFinished);
    job->start();
}

void EwsReplyPrivate::processJob(KDSoapJob *job)
{
    // TODO make this pure virtual
}

void EwsReplyPrivate::jobFinished(KDSoapJob *job)
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

#include "moc_EwsReply.cpp"
