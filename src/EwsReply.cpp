/***************************************************************************
 *   Copyright (C) 2013 Daniel Nicoletti <dantti12@gmail.com>              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 ***************************************************************************/

#include "EwsReply.h"
#include "EwsConnection.h"
#include "EwsUtils.h"

#include <QStringBuilder>
#include <QDebug>

EwsReply::EwsReply(QNetworkReply *reply, const QString &requestName) :
    m_reply(reply),
    m_requestName(requestName),
    m_responseCode(NoError),
    m_parseFailed(false)
{
    connect(reply, SIGNAL(finished()), SLOT(requestFinished()));
}

EwsReply::EwsReply(void *reply) :
//    m_reply(reply),
//    m_requestName(requestName),
    m_responseCode(NoError),
    m_parseFailed(false)
{
}

EwsReply::~EwsReply()
{
    if (m_reply) {
        m_reply->deleteLater();
    }
}

bool EwsReply::error() const
{
    return m_parseFailed || m_reply->error() || m_responseCode;
}

EwsReply::ResponseCode EwsReply::responseCode() const
{
    return m_responseCode;
}

QString EwsReply::errorMessage() const
{
    if (m_reply->error()) {
        return m_reply->errorString();
    } else {
        return m_errorMessage;
    }
}

QDomDocument EwsReply::document() const
{
    return m_replyDocument;
}

bool EwsReply::validateResponse(EwsRequest &message)
{
    ESoapElement element = message.body();
    element = element.firstChildTypedElement(m_requestName % QLatin1String("Response"), EWS_MESSAGES_NS);
    if (element.isNull()) {
        qWarning() << Q_FUNC_INFO << "Failed to find <*Response> element";
        return false;
    }

    element = element.firstChildTypedElement(QLatin1String("ResponseMessages"), EWS_MESSAGES_NS);
    if (element.isNull()) {
        qWarning() << Q_FUNC_INFO << "Failed to find <ResponseMessages> element";
        return false;
    }

    ESoapElement response = element.firstChildTypedElement(m_requestName % QLatin1String("ResponseMessage"), EWS_MESSAGES_NS);
    if (response.isNull()) {
        qWarning() << Q_FUNC_INFO << "Failed to find <*ResponseMessage> element";
        return false;
    }

    if (response.attribute(QLatin1String("ResponseClass")) == QLatin1String("Success")) {
        return parseDocument(response);
    } else {
        qWarning() << Q_FUNC_INFO << m_requestName;
        qWarning() << message.toString(2);

        element = response.firstChildTypedElement(QLatin1String("MessageText"), EWS_MESSAGES_NS);
        if (!element.isNull()) {
            m_errorMessage = element.text();
        }

        element = response.firstChildTypedElement(QLatin1String("ResponseCode"), EWS_MESSAGES_NS);
        if (!element.isNull()) {
            int code = EwsUtils::enumFromString<EwsReply>("ResponseCode", element.text());
            m_responseCode = static_cast<EwsReply::ResponseCode>(code);
        }

        return false;
    }
}

bool EwsReply::parseDocument(ESoapElement &message)
{
    Q_UNUSED(message)

    return true;
}

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
        m_replyDocument.setContent(reply->readAll());
        EwsRequest message(m_replyDocument);
        if (message.parserError()) {
            m_parseFailed = true;
        } else {
            m_parseFailed = !validateResponse(message);
        }
        emit finished();
    }
}
