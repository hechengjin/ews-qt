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

#ifndef EWSREPLY_P_H
#define EWSREPLY_P_H

#include <QObject>

#include "reply.h"
#include "wsdl_Services.h"

namespace Ews {

class ReplyPrivate : public QObject
{
    Q_OBJECT
public:
    explicit ReplyPrivate(KDSoapJob *job, QObject *parent);

    QString error;

protected:
    /**
     * This is only called when the job
     * has finished without errors,
     *
     * DO NOT EMIT FINISHED
     */
    virtual void processJob(KDSoapJob *job) = 0;

    void setResponseMessage(const TNS__ResponseMessageType &message);
    TNS__ResponseMessageType responseMessage;

signals:
    void finished();

private:
    friend class Reply;
    void jobFinished(KDSoapJob *job);
};

}

#endif // EWSREPLY_P_H
