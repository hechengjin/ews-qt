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

#include "EwsRequest.h"
#include "EwsConnection.h"

#include <QDebug>

#define EWS_AUTODISCOVER_REQUEST_SCHEMA  "http://schemas.microsoft.com/exchange/autodiscover/outlook/requestschema/2006"
#define EWS_AUTODISCOVER_RESPONSE_SCHEMA "http://schemas.microsoft.com/exchange/autodiscover/outlook/responseschema/2006a"

using namespace Ews;

Request::Request(const QDomDocument &document) :
    ESoapMessage(document)
{
}

Request::Request(const QString &method, ServerVersion version)
{
    init(version);

    m_method = createElement(method);
    m_method.setDefaultNamespace(EWS_MESSAGES_NS);

    body().addNamespace(EWS_MESSAGES_NS);
    body().addNamespace(EWS_TYPES_NS);
    body().appendChild(m_method);
}

ESoapElement Request::method() const
{
    return m_method;
}

QString Request::methodName() const
{
    return m_method.nodeName();
}

QDomDocument Request::autoDiscover(const QString &emailAddress)
{
    QDomDocument ret;
    QDomImplementation impl;
    ret = impl.createDocument(QString(),
                              QString(),
                              QDomDocumentType());
    QDomElement autoDiscover = ret.createElementNS(QLatin1String(EWS_AUTODISCOVER_REQUEST_SCHEMA),
                                                   QLatin1String("Autodiscover"));
    QDomElement requestNode = ret.createElement(QLatin1String("Request"));
    QDomElement emailNode = ret.createElement(QLatin1String("EMailAddress"));
    emailNode.appendChild(ret.createTextNode(emailAddress));
    QDomElement response = ret.createElement(QLatin1String("AcceptableResponseSchema"));
    response.appendChild(ret.createTextNode(QLatin1String(EWS_AUTODISCOVER_RESPONSE_SCHEMA)));

    requestNode.appendChild(emailNode);
    requestNode.appendChild(response);
    autoDiscover.appendChild(requestNode);
    ret.appendChild(autoDiscover);

    return ret;
}

void Request::init(ServerVersion version)
{
    QString versionString;
    switch (version) {
    case Exchange2010_SP2:
        versionString = QLatin1String("Exchange2010_SP2");
        break;
    case Exchange2010_SP1:
        versionString = QLatin1String("Exchange2010_SP1");
        break;
    case Exchange2010:
        versionString = QLatin1String("Exchange2010");
        break;
    case Exchange2007_SP1:
        versionString = QLatin1String("Exchange2007_SP1");
        break;
    default:
        versionString = QLatin1String("Exchange2007");
        break;
    }
    createTypedHeaderElement(QLatin1String("RequestServerVersion"), EWS_TYPES_NS)
            .setAttribute(QLatin1String("Version"), versionString);
}
