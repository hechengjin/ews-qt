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

#include "EwsAutoDiscover.h"

#include "EwsConnection.h"
#include "EwsRequest.h"
#include "EwsAutoDiscoverReply.h"

#include <QDnsLookup>
#include <QStringBuilder>
#include <QDebug>

EwsAutoDiscover::EwsAutoDiscover(QObject *parent) :
    QObject(parent),
    m_connection(new EwsConnection(this)),
    m_srvLookupDone(false),
    m_valid(false)
{
}

void EwsAutoDiscover::autodiscover(const QString &emailAddress, const QString &username, const QString &password)
{
    m_uri.setHost(emailAddress.section(QLatin1Char('@'), 1, 1));
    m_uri.setUserName(username);
    m_uri.setPassword(password);
    m_emailAddress = emailAddress;
    m_message = EwsRequest::autoDiscover(emailAddress);

    performAutoDiscover(m_uri);
}

bool EwsAutoDiscover::isValid() const
{
    return m_valid;
}

QString EwsAutoDiscover::errorMessage() const
{
    return m_errorMessage;
}

QUrl EwsAutoDiscover::uri() const
{
    return m_uri;
}

QString EwsAutoDiscover::emailAddress() const
{
    return m_emailAddress;
}

QString EwsAutoDiscover::asUrl() const
{
    return m_asUrl;
}

QString EwsAutoDiscover::oabUrl() const
{
    return m_oabUrl;
}

void EwsAutoDiscover::requestFinished()
{
    EwsAutoDiscoverReply *reply = qobject_cast<EwsAutoDiscoverReply*>(sender());
    if (m_replies.isEmpty()) {
        return;
    }

    m_replies.removeOne(reply);
    if (!reply->error()) {
        if (parseAutoDiscover(reply->document())) {
            foreach (EwsAutoDiscoverReply *reply, m_replies) {
                reply->deleteLater();
            }

            m_uri = reply->url();
            m_valid = true;
            m_errorMessage = QString();
            m_replies.clear();
            emit finished();
            return;
        }
    } else if (reply->error() == QNetworkReply::AuthenticationRequiredError) {
        qDebug() << Q_FUNC_INFO << reply->url() << reply->error() << reply->errorMessage();
        foreach (EwsAutoDiscoverReply *reply, m_replies) {
            reply->deleteLater();
        }

        m_uri = QUrl();
        m_valid = false;
        m_errorMessage = reply->errorMessage();
        m_replies.clear();
        emit finished();
        return;
    } else {
        m_errorMessage = reply->errorMessage();
    }

    if (m_replies.isEmpty() && m_srvLookupDone) {
        emit finished();
    }
}

void EwsAutoDiscover::resultsReady()
{
    m_srvLookupDone = true;

    QDnsLookup *dns = qobject_cast<QDnsLookup*>(sender());
    foreach (const QDnsServiceRecord &record, dns->serviceRecords()) {
        if (record.target() != m_uri.host()) {
            QUrl newServer = m_uri;
            newServer.setHost(record.target());
            performAutoDiscover(newServer);

            if (record.port() != 80 || record.port() != 443) {
                newServer.setPort(record.port());
                performAutoDiscover(newServer);
            }
        }
    }

    if (m_replies.isEmpty()) {
        emit finished();
    }
    dns->deleteLater();
}

void EwsAutoDiscover::performAutoDiscover(const QUrl &uri)
{
    /**
     * @brief http://msdn.microsoft.com/en-us/library/ee332364.aspx
     * The steps here are described at that page, Evolotuion
     * has a note where some firewalls drop the packages which would
     * lead to long timeouts so we process all urls at once and use
     * the first sucessfull one
     */
    EwsAutoDiscoverReply *reply;

    QUrl url1 = autodiscoverUrl(QLatin1String("https"), uri);
    reply = m_connection->post(url1, m_message);
    connect(reply, &EwsAutoDiscoverReply::finished,
            this, &EwsAutoDiscover::requestFinished);
    m_replies << reply;

    QUrl url2 = uri;
    url2.setHost(QLatin1String("autodiscover.") % uri.host());
    url2 = autodiscoverUrl(QLatin1String("https"), uri);
    reply = m_connection->post(url2, m_message);
    connect(reply, &EwsAutoDiscoverReply::finished,
            this, &EwsAutoDiscover::requestFinished);
    m_replies << reply;

    QUrl url3 = uri;
    url3.setHost(QLatin1String("autodiscover.") % uri.host());
    url3 = autodiscoverUrl(QLatin1String("http"), uri);
    reply = m_connection->get(url3, m_message);
    connect(reply, &EwsAutoDiscoverReply::finished,
            this, &EwsAutoDiscover::requestFinished);
    m_replies << reply;

    if (!m_srvLookupDone) {
        // Create a DNS lookup.
        QDnsLookup *dns = new QDnsLookup(this);
        connect(dns, &QDnsLookup::finished,
                this, &EwsAutoDiscover::resultsReady);

        // Find the autodiscover servers from the DNS SRV entry
        dns->setType(QDnsLookup::SRV);
        dns->setName(QLatin1String("_autodiscover._tcp.") % uri.host());
        dns->lookup();
    }
}

bool EwsAutoDiscover::parseAutoDiscover(const QDomDocument &document)
{
    qDebug() << Q_FUNC_INFO;

    // print out the element names of all elements that are direct children
    // of the outermost element.
    QDomElement docElem = document.documentElement();
    if (docElem.tagName() != QLatin1String("Autodiscover")) {
        qWarning() << Q_FUNC_INFO << "Failed to find <Autodiscover> element";
        return false;
    }

    docElem = docElem.firstChildElement(QLatin1String("Response"));
    if (docElem.isNull()) {
        qWarning() << Q_FUNC_INFO << "Failed to find <Response> element";
        return false;
    }

    QDomElement account = docElem.firstChildElement(QLatin1String("Account"));
    if (account.isNull()) {
        docElem = docElem.firstChildElement(QLatin1String("Error"));
        if (docElem.isNull()) {
            qWarning() << Q_FUNC_INFO << "Failed to find <Account> or <Error> elements";
        } else {
            QString text;
            QDomElement error = docElem.firstChildElement(QLatin1String("Message"));
            if (!error.isNull()) {
                text = error.text();
            }

            error = docElem.firstChildElement(QLatin1String("ErrorCode"));
            if (!error.isNull()) {
                m_errorMessage = QString("%1 (%2)").arg(text, error.text());
            } else {
                m_errorMessage = text;
            }
        }

        return false;
    }

    QDomElement action = account.firstChildElement(QLatin1String("Action"));
    if (action.isNull()) {
        qWarning() << Q_FUNC_INFO << "Failed to find <Action> element";
        return false;
    }

    if (action.text() == QLatin1String("settings")) {
        QDomElement protocol = account.firstChildElement(QLatin1String("Protocol"));
        while (!protocol.isNull()) {
            if (parseAutoDiscoverProtocol(protocol)) {
                return true;
            }

            protocol = account.nextSiblingElement(QLatin1String("Protocol"));
        }
    } else if (action.text() == QLatin1String("redirectAddr")) {
        // From the specification we should start from step 1
        // which means doing another SRV lookup to help us find out
        // the proper configuration
        m_srvLookupDone = false;
        m_emailAddress = action.text();
        performAutoDiscover(m_uri);
    } else if (action.text() == QLatin1String("redirectUrl")) {
        QUrl uri = m_uri;
        uri.setHost(action.text());
        performAutoDiscover(uri);
    } else {
        qWarning() << Q_FUNC_INFO << "AutoDiscover action not handled" << action.text();
    }

    return false;
}

bool EwsAutoDiscover::parseAutoDiscoverProtocol(const QDomElement &element)
{
    QDomElement urlElem;
    urlElem = element.firstChildElement(QLatin1String("ASUrl"));
    if (!urlElem.isNull()) {
        m_asUrl = urlElem.text();
    }

    urlElem = element.firstChildElement(QLatin1String("OABUrl"));
    if (!urlElem.isNull()) {
        m_oabUrl = urlElem.text();
    }
    qWarning() << Q_FUNC_INFO << m_asUrl << m_oabUrl;

    return !m_asUrl.isEmpty() && !m_oabUrl.isEmpty();
}

QUrl EwsAutoDiscover::autodiscoverUrl(const QString &scheme, const QUrl &url)
{
    QUrl ret;
    ret = scheme % QLatin1String("://") % url.authority() % QLatin1String("/autodiscover/autodiscover.xml");
    return ret;
}
