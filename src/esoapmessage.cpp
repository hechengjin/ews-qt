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

#include "esoapmessage.h"

#include "esoapnamespaces.h"

#define SOAPv11_ENVELOPE    "http://schemas.xmlsoap.org/soap/envelope/"
#define SOAPv11_ENCODING    "http://schemas.xmlsoap.org/soap/encoding/"
#define SOAPv11_ACTORNEXT   "http://schemas.xmlsoap.org/soap/actor/next"

#define XML_SCHEMA          "http://www.w3.org/1999/XMLSchema"
#define XML_SCHEMA_INSTANCE "http://www.w3.org/1999/XMLSchema-instance"
#define XML_NAMESPACE       "http://www.w3.org/XML/1998/namespace"

#include <QStringBuilder>
#include <QNetworkRequest>
#include <QDebug>

ESoapMessage::ESoapMessage() :
    m_namespaces(ESoapNamespaces::instance()),
    m_parserError(false)
{
    QDomDocumentType type;
    type.setPrefix(QLatin1String("1.0"));
    QDomImplementation impl;
    QDomDocument::operator =(impl.createDocument(QString(),
                                                 QString(),
                                                 type));

    m_namespaces->registerNamespace("soap", SOAPv11_ENVELOPE);
    m_namespaces->registerNamespace("SOAP-ENC", SOAPv11_ENCODING);
    m_namespaces->registerNamespace("xsi", XML_SCHEMA_INSTANCE);
    m_namespaces->registerNamespace("xsd", XML_SCHEMA);

    m_envelope = createElementNS(SOAPv11_ENVELOPE, QLatin1String("Envelope"));
    m_envelope.setPrefix(QLatin1String("soap"));

//    m_envelope.setAttribute(QLatin1String("xmlns:") % QLatin1String("SOAP-ENC"),
//                            SOAPv11_ENCODING);

    m_envelope.setAttribute(QLatin1String("xmlns:") % QLatin1String("xsd"),
                            XML_SCHEMA);

    m_envelope.setAttribute(QLatin1String("xmlns:") % QLatin1String("xsi"),
                            XML_SCHEMA_INSTANCE);

    m_header = createTypedElement(QLatin1String("Header"), SOAPv11_ENVELOPE);
    m_envelope.appendChild(m_header);
    appendChild(m_envelope);
}

ESoapMessage::ESoapMessage(const QDomDocument &other) :
    QDomDocument(other),
    m_namespaces(new ESoapNamespaces),
    m_parserError(false)
{
    // We need to extract the namespaces from the message,
    // so that we can use find items with their uri
    m_envelope = documentElement();
    m_envelope.setESoapNamespaces(m_namespaces);
    extractNamespaces(m_envelope);

    if (!m_envelope.equalNS(QLatin1String("Envelope"), SOAPv11_ENVELOPE)) {
        qWarning() << Q_FUNC_INFO << "Failed to find <Envelope> element";
        m_parserError = true;
    }

    m_header = m_envelope.firstChildTypedElement(QLatin1String("Header"), SOAPv11_ENVELOPE);
    if (m_header.isNull()) {
        qWarning() << Q_FUNC_INFO << "Failed to find <Header> element";
        m_parserError = true;
    }

    m_body = m_envelope.firstChildTypedElement(QLatin1String("Body"), SOAPv11_ENVELOPE);
    if (m_body.isNull()) {
        qWarning() << Q_FUNC_INFO << "Failed to find <Body> element";
        m_parserError = true;
    }
}

void ESoapMessage::print()
{
    qDebug();
    qDebug() << toString(2);
    qDebug();
}

bool ESoapMessage::parserError()
{
    return m_parserError;
}

ESoapElement ESoapMessage::envelope() const
{
    return m_envelope;
}

ESoapElement ESoapMessage::header()
{
    return m_header;
}

ESoapElement ESoapMessage::body()
{
    if (!m_body.isNull()) {
        return m_body;
    }

    m_body = createTypedElement(QLatin1String("Body"), SOAPv11_ENVELOPE);

    m_envelope.appendChild(m_body);
    return m_body;
}

ESoapElement ESoapMessage::createElement(const QString &name)
{
    return QDomDocument::createElement(name);
}

ESoapElement ESoapMessage::createTypedElement(const QString &name, const QString &nsUri)
{
    QString prefix = ESoapNamespaces::instance()->prefixFor(nsUri);
    ESoapElement element = createElement(prefix % QLatin1Char(':') % name);
    element.setPrefixNS(prefix, nsUri);

    return element;
}

ESoapElement ESoapMessage::createTypedHeaderElement(const QString &name, const QString &nsUri)
{
    ESoapElement element = createTypedElement(name, nsUri);
    m_header.appendChild(element);
    return element;
}

void ESoapMessage::extractNamespaces(const QDomElement &element)
{
    QDomNamedNodeMap map = element.attributes();
    for (int i = 0; i < map.length(); ++i) {
        QDomNode node = map.item(i);
        if (node.nodeName().startsWith(QLatin1String("xmlns:"))) {
            QString prefix = node.nodeName().section(QLatin1Char(':'), 1, 1);
            m_namespaces->registerNamespace(prefix, node.toAttr().value());
        }
    }

    QDomNodeList childList = element.childNodes();
    for (int i = 0; i < childList.length(); ++i) {
        QDomNode node = childList.item(i);
        if (node.isElement()) {
            extractNamespaces(node.toElement());
        }
    }
}
