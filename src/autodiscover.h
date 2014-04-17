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

#ifndef EWSAUTODISCOVER_H
#define EWSAUTODISCOVER_H

#include "export.h"

#include <QObject>
#include <QUrl>
#include <QDomDocument>

namespace Ews {

class Connection;
class AutoDiscoverReply;
class EWS_EXPORT AutoDiscover : public QObject
{
    Q_OBJECT
public:
    explicit AutoDiscover(QObject *parent = 0);
    
    void autodiscover(const QString &emailAddress, const QString &serverAddress, const QString &username, const QString &password);
    bool isValid() const;
    QString errorMessage() const;
    QUrl uri() const;
    QString emailAddress() const;
    QString internalASUrl() const;
    QString externalASUrl() const;
    bool authRequired() const;
    bool cancelled();

public slots:
    void cancel();

signals:
    void finished();

private slots:

    void requestFinished();
    void resultsReady();

private:
    void performAutoDiscover(const QUrl &uri);
    bool parseAutoDiscover(const QDomDocument &document);
    void parseAutoDiscoverProtocol(const QDomElement &element, bool accountTypeIsEmail);
    QUrl autodiscoverUrl(const QString &scheme, const QUrl &url);

    Connection *m_connection;
    QList<AutoDiscoverReply*> m_replies;
    bool m_srvLookupDone;
    bool m_valid;
    bool m_cancelled = false;
    QUrl m_uri;
    QDomDocument m_message;
    QString m_emailAddress;
    QString m_internalASUrl;
    QString m_externalASUrl;
    QString m_errorMessage;
    bool m_authRequired = false;
};

}

#endif // EWSAUTODISCOVER_H
