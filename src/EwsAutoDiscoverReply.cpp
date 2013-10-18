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

#include "EwsAutoDiscoverReply.h"
#include "EwsConnection.h"

#include <QDebug>

EwsAutoDiscoverReply::EwsAutoDiscoverReply(const QDomDocument &document, EwsConnection *connection) :
    m_document(document),
    m_connection(connection),
    m_reply(0),
    m_redirects(0)
{
}

EwsAutoDiscoverReply::~EwsAutoDiscoverReply()
{
    if (m_reply) {
        m_reply->deleteLater();
    }
}

void EwsAutoDiscoverReply::setReply(QNetworkReply *reply)
{
    if (m_reply) {
        m_reply->deleteLater();
    }
    m_reply = reply;
    connect(reply, SIGNAL(finished()), SLOT(requestFinished()));
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)), SLOT(sslErrors(QList<QSslError>)));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), SLOT(error(QNetworkReply::NetworkError)));
    ++m_redirects;
}

QUrl EwsAutoDiscoverReply::url() const
{
    if (m_reply) {
        return m_reply->url();
    }
    return QUrl();
}

QNetworkReply::NetworkError EwsAutoDiscoverReply::error() const
{
    if (m_reply) {
        return m_reply->error();
    }
    return QNetworkReply::NoError;
}

QString EwsAutoDiscoverReply::errorMessage() const
{
    if (m_reply) {
        return m_reply->errorString();
    }
    return QString();
}

QDomDocument EwsAutoDiscoverReply::document() const
{
    return m_replyDocument;
}

void EwsAutoDiscoverReply::requestFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    qDebug() << Q_FUNC_INFO << reply->url().host() << reply->error();
    if (reply->error()) {
        qDebug() << Q_FUNC_INFO << QString("Network transport error (%1): %2").arg(reply->error()).arg(reply->errorString());
        qDebug() << Q_FUNC_INFO << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << Q_FUNC_INFO << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute);
        qDebug() << Q_FUNC_INFO << reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

        QUrl url = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
        if (url.isEmpty()) {
            emit finished();
        } else {
            // Microsoft documentation recommends following no more than 10 redirects
            if (m_redirects > 10) {
                emit finished();
            } else {
                qDebug() << Q_FUNC_INFO << "Redirecting..." << url;
                setReply(m_connection->postDocument(url, m_document));
                reply->deleteLater();
            }
        }
    } else {
        m_replyDocument.setContent(reply->readAll());
        emit finished();
    }
}

void EwsAutoDiscoverReply::error(QNetworkReply::NetworkError error)
{
    qDebug() << Q_FUNC_INFO << error;
}

void EwsAutoDiscoverReply::sslErrors(const QList<QSslError> &errors)
{
    qDebug() << Q_FUNC_INFO << errors.size();
}
