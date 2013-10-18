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

#ifndef EWSAUTODISCOVERREPLY_H
#define EWSAUTODISCOVERREPLY_H

#include "ewsexport.h"

#include <QNetworkReply>
#include <QDomDocument>

class EwsConnection;
class EWS_EXPORT EwsAutoDiscoverReply : public QObject
{
    Q_OBJECT
public:
    EwsAutoDiscoverReply(const QDomDocument &document, EwsConnection *connection);
    ~EwsAutoDiscoverReply();

    void setReply(QNetworkReply *reply);
    QUrl url() const;
    QNetworkReply::NetworkError error() const;
    QString errorMessage() const;
    QDomDocument document() const;

signals:
    void finished();

private slots:
    void requestFinished();
    void error(QNetworkReply::NetworkError error);
    void sslErrors(const QList<QSslError> &errors);

private:
    QDomDocument m_document;
    QDomDocument m_replyDocument;
    EwsConnection *m_connection;
    QNetworkReply *m_reply;
    int m_redirects;
};

#endif // EWSAUTODISCOVERREPLY_H
