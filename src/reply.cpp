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

Reply::Reply(ReplyPrivate *priv) :
    d_ptr(priv)
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
    return !d->error.isEmpty();
}

QString Reply::errorMessage() const
{
    Q_D(const Reply);
    return d->error;
}

Reply::ResponseCode Reply::responseCode() const
{
    Q_D(const Reply);
    return static_cast<Reply::ResponseCode>(d->responseMessage.responseCode().type());
}

QString Reply::messageText() const
{
    Q_D(const Reply);
    return d->responseMessage.messageText();
}

int Reply::descriptiveLinkKey() const
{
    Q_D(const Reply);
    return d->responseMessage.descriptiveLinkKey();
}

Reply::ResponseClass Reply::responseClass() const
{
    Q_D(const Reply);
    return static_cast<Reply::ResponseClass>(d->responseMessage.responseClass().type());
}

ReplyPrivate::ReplyPrivate(KDSoapJob *job, QObject *parent)
{
    parent->setParent(job);
    connect(job, &KDSoapJob::finished,
            this, &ReplyPrivate::jobFinished);
    job->start();
}

void ReplyPrivate::jobFinished(KDSoapJob *job)
{
    qDebug() << job->reply();
    qDebug() << job->faultAsString();
    if (job->isFault()) {
        error = job->faultAsString();
    } else {
        // Tell the specialization to
        // do their job
        processJob(job);
    }
    emit finished();
}


void Ews::ReplyPrivate::setResponseMessage(const TNS__ResponseMessageType &message)
{
    responseMessage = message;
}
