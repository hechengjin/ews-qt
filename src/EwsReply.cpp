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

EwsReply::EwsReply(QObject *exchangeServices) :
    d_ptr(new EwsReplyPrivate),
    m_responseCode(NoError),
    m_parseFailed(false)
{
    KDSoapJob *job = qobject_cast<KDSoapJob*>(exchangeServices);

    connect(job, &KDSoapJob::finished,
            d_ptr, &EwsReplyPrivate::finished);
}

EwsReply::~EwsReply()
{
    delete d_ptr;
}

bool EwsReply::error() const
{
    return m_parseFailed || m_responseCode;
}

EwsReply::ResponseCode EwsReply::responseCode() const
{
    return m_responseCode;
}

QString EwsReply::errorMessage() const
{
    return m_errorMessage;
}

//bool EwsReply::validateResponse(EwsRequest &message)
//{
//    ESoapElement element = message.body();
//    element = element.firstChildTypedElement(m_requestName % QLatin1String("Response"), EWS_MESSAGES_NS);
//    if (element.isNull()) {
//        qWarning() << Q_FUNC_INFO << "Failed to find <*Response> element";
//        return false;
//    }

//    element = element.firstChildTypedElement(QLatin1String("ResponseMessages"), EWS_MESSAGES_NS);
//    if (element.isNull()) {
//        qWarning() << Q_FUNC_INFO << "Failed to find <ResponseMessages> element";
//        return false;
//    }

//    ESoapElement response = element.firstChildTypedElement(m_requestName % QLatin1String("ResponseMessage"), EWS_MESSAGES_NS);
//    if (response.isNull()) {
//        qWarning() << Q_FUNC_INFO << "Failed to find <*ResponseMessage> element";
//        return false;
//    }

//    if (response.attribute(QLatin1String("ResponseClass")) == QLatin1String("Success")) {
//        return parseDocument(response);
//    } else {
//        qWarning() << Q_FUNC_INFO << m_requestName;
//        qWarning() << message.toString(2);

//        element = response.firstChildTypedElement(QLatin1String("MessageText"), EWS_MESSAGES_NS);
//        if (!element.isNull()) {
//            m_errorMessage = element.text();
//        }

//        element = response.firstChildTypedElement(QLatin1String("ResponseCode"), EWS_MESSAGES_NS);
//        if (!element.isNull()) {
//            int code = EwsUtils::enumFromString<EwsReply>("ResponseCode", element.text());
//            m_responseCode = static_cast<EwsReply::ResponseCode>(code);
//        }

//        return false;
//    }
//}

//bool EwsReply::parseDocument(ESoapElement &message)
//{
//    Q_UNUSED(message)

//    return true;
//}

void EwsReply::requestFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    qDebug() << Q_FUNC_INFO << reply;
    if (reply->error()) {        
        qDebug() << Q_FUNC_INFO << QString("Network transport error (%1): %2").arg(reply->error()).arg(reply->errorString());
//        qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
//        qDebug() << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute);
//        qDebug() << reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
        emit finished();
    } else {

        emit finished();
    }
}


void EwsReplyPrivate::deleteFolderDone(const TNS__DeleteFolderResponseType &deleteFolderResult)
{
    qWarning() << Q_FUNC_INFO << deleteFolderResult.responseMessages().deleteFolderResponseMessage().size();
}

void EwsReplyPrivate::handleError(const KDSoapMessage &fault)
{
    qWarning() << Q_FUNC_INFO << fault.faultAsString();
    //    emit finished();
}

void EwsReplyPrivate::finished(KDSoapJob *job)
{
    qWarning() << Q_FUNC_INFO << job;

//    emit qfinished();
}
