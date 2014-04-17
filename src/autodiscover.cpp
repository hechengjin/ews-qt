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

#include "autodiscover.h"

#include "connection.h"
#include "request.h"
#include "autodiscoverreply.h"

#include <QDnsLookup>
#include <QStringBuilder>
#include <QDebug>

using namespace Ews;

AutoDiscover::AutoDiscover(QObject *parent) :
    QObject(parent),
    m_connection(new Ews::Connection(this)),
    m_srvLookupDone(false),
    m_valid(false)
{
}

void AutoDiscover::autodiscover(const QString &emailAddress, const QString &serverAddress, const QString &username, const QString &password)
{
    m_uri.setHost(serverAddress);
    m_uri.setUserName(username);
    m_uri.setPassword(password);
    m_emailAddress = emailAddress;
    m_message = Request::autoDiscover(emailAddress);
    m_authRequired = false;
    m_errorMessage.clear();

    performAutoDiscover(m_uri);
}

bool AutoDiscover::isValid() const
{
    return m_valid;
}

QString AutoDiscover::errorMessage() const
{
    return m_errorMessage;
}

QUrl AutoDiscover::uri() const
{
    return m_uri;
}

QString AutoDiscover::emailAddress() const
{
    return m_emailAddress;
}

QString AutoDiscover::internalASUrl() const
{
    return m_internalASUrl;
}

QString AutoDiscover::externalASUrl() const
{
    return m_externalASUrl;
}

bool AutoDiscover::authRequired() const
{
    return m_authRequired;
}

bool AutoDiscover::cancelled()
{
    return m_cancelled;
}

void AutoDiscover::cancel()
{
    while (!m_replies.isEmpty()) {
        AutoDiscoverReply *reply = m_replies.takeFirst();
        delete reply;
    }

    m_valid = false;
    m_cancelled = true;
    m_errorMessage = QString();
    emit finished();
}

void AutoDiscover::requestFinished()
{
    AutoDiscoverReply *reply = qobject_cast<AutoDiscoverReply*>(sender());
    if (m_replies.isEmpty()) {
        return;
    }

    m_replies.removeOne(reply);
    if (!reply->error() && !reply->document().isNull()) {
        if (parseAutoDiscover(reply->document())) {
            foreach (AutoDiscoverReply *reply, m_replies) {
                reply->deleteLater();
            }
            qDebug() << reply->document().toString(2);

            m_uri = reply->url();
            m_valid = true;
            m_errorMessage = QString();
            m_replies.clear();
            emit finished();
            return;
        }
    } else if (reply->error() == QNetworkReply::AuthenticationRequiredError) {
        qDebug() << Q_FUNC_INFO << reply->url().host() << reply->error() << reply->errorMessage();
        foreach (AutoDiscoverReply *reply, m_replies) {
            reply->deleteLater();
        }

        m_uri = reply->url();
        m_valid = false;
        m_authRequired = true;
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

void AutoDiscover::resultsReady()
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

void AutoDiscover::performAutoDiscover(const QUrl &uri)
{
    /**
     * @brief http://msdn.microsoft.com/en-us/library/ee332364.aspx
     * The steps here are described at that page, Evolotuion
     * has a note where some firewalls drop the packages which would
     * lead to long timeouts so we process all urls at once and use
     * the first sucessfull one
     */
    AutoDiscoverReply *reply;

    QUrl url1 = autodiscoverUrl(QLatin1String("https"), uri);
    reply = m_connection->post(url1, m_message);
    connect(reply, &AutoDiscoverReply::finished,
            this, &AutoDiscover::requestFinished);
    m_replies << reply;

    QUrl url2 = uri;
    url2.setHost(QLatin1String("autodiscover.") % uri.host());
    url2 = autodiscoverUrl(QLatin1String("https"), url2);
    reply = m_connection->post(url2, m_message);
    connect(reply, &AutoDiscoverReply::finished,
            this, &AutoDiscover::requestFinished);
    m_replies << reply;

    QUrl url3 = uri;
    url3.setHost(QLatin1String("autodiscover.") % uri.host());
    url3 = autodiscoverUrl(QLatin1String("http"), url3);
    reply = m_connection->get(url3, m_message);
    connect(reply, &AutoDiscoverReply::finished,
            this, &AutoDiscover::requestFinished);
    m_replies << reply;

    if (!m_srvLookupDone) {
        // Create a DNS lookup.
        QDnsLookup *dns = new QDnsLookup(this);
        connect(dns, &QDnsLookup::finished,
                this, &AutoDiscover::resultsReady);

        // Find the autodiscover servers from the DNS SRV entry
        dns->setType(QDnsLookup::SRV);
        dns->setName(QLatin1String("_autodiscover._tcp.") % uri.host());
        dns->lookup();
    }
}

bool AutoDiscover::parseAutoDiscover(const QDomDocument &document)
{
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

    QDomElement accountType = account.firstChildElement(QLatin1String("AccountType"));
    if (accountType.isNull()) {
        qWarning() << Q_FUNC_INFO << "Failed to find <AccountType> element";
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
            parseAutoDiscoverProtocol(protocol,
                                      accountType.text() == QLatin1String("email"));

            protocol = protocol.nextSiblingElement(QLatin1String("Protocol"));
        }

        qWarning() << Q_FUNC_INFO << m_externalASUrl << m_internalASUrl;

        if (!m_externalASUrl.isEmpty() || !m_internalASUrl.isEmpty()) {
            return true;
        } else {
            m_internalASUrl.clear();
            m_externalASUrl.clear();
            return false;
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

void AutoDiscover::parseAutoDiscoverProtocol(const QDomElement &element, bool accountTypeIsEmail)
{
    QDomElement typeElement = element.firstChildElement(QLatin1String("Type"));
    if (typeElement.isNull()) {
        qWarning() << Q_FUNC_INFO << "Failed to find <Type> element";
        return;
    } else if (typeElement.text() != QLatin1String("EXCH") &&
               typeElement.text() != QLatin1String("EXPR")) {
        return;
    }

    QDomElement serverElement = element.firstChildElement(QLatin1String("Server"));
    if (serverElement.isNull()) {
        qWarning() << Q_FUNC_INFO << "Failed to find <Server> element";
        return;
    }

    QDomElement urlElem = element.firstChildElement(QLatin1String("ASUrl"));
    if (!urlElem.isNull()) {
        QUrl url = urlElem.text();
        url.setHost(serverElement.text());
        if (typeElement.text() == QLatin1String("EXCH")) {
            // The protocol that is used to connect to the server is Exchange RPC.
            m_internalASUrl = url.toString();
        } else if (typeElement.text() == QLatin1String("EXPR") && accountTypeIsEmail) {
            // The protocol that is used to connect to the server is Exchange RPC
            // over HTTP, using an RPC proxy server.
            // This is only applicable when the AccountType (POX) element is set to email.
            m_externalASUrl = url.toString();
        }
    }
}

QUrl AutoDiscover::autodiscoverUrl(const QString &scheme, const QUrl &url)
{
    QUrl ret;
    ret = scheme % QLatin1String("://") % url.authority() % QLatin1String("/autodiscover/autodiscover.xml");
    return ret;
}
