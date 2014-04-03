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

#include "esoapelement.h"
#include "esoapnamespaces.h"

#include <QStringBuilder>
#include <QDebug>

ESoapElement::ESoapElement() :
    m_namespaces(ESoapNamespaces::instance())
{
}

ESoapElement::ESoapElement(const ESoapNamespaces::Ptr &namespaces) :
    m_namespaces(namespaces)
{
}

ESoapElement::ESoapElement(const QDomElement &other) :
    QDomElement(other),
    m_namespaces(ESoapNamespaces::instance())
{
}

bool ESoapElement::equalNS(const QString &name, const QString &nsUri) const
{
    return tagName() == m_namespaces->prefixFor(nsUri) % QLatin1Char(':') % name;
}

QDomNode ESoapElement::appendChild(const ESoapElement &newChild)
{
    ESoapElement element(newChild);
    QString prefix = element.prefix();
//    qDebug() << Q_FUNC_INFO << prefix << element.nodeName();
    if (!prefix.isEmpty()) {
        QString nsUri = findParentNamespace(*this, prefix);
        if (nsUri.isEmpty()) {
//            qDebug() << Q_FUNC_INFO << "Prefix not found in parent adding it" << prefix;
            element.setAttribute(QLatin1String("xmlns:") % prefix, element.nsUri());
        }
    }

    return QDomElement::appendChild(element);
}

void ESoapElement::setPrefixNS(const QString &prefix, const QString &nsUri)
{
    m_prefix = prefix;
    m_nsUri = nsUri;
}

void ESoapElement::setText(const QString &text)
{
    QDomElement::appendChild(ownerDocument().createTextNode(text));
}

QString ESoapElement::prefix() const
{
    return m_prefix;
}

QString ESoapElement::nsUri() const
{
    return m_nsUri;
}

void ESoapElement::addNamespace(const QString &nsUri)
{
    QString prefix = ESoapNamespaces::instance()->prefixFor(nsUri);
    setAttribute(QLatin1String("xmlns:") % prefix, nsUri);
}

void ESoapElement::setDefaultNamespace(const QString &nsUri)
{
    setAttribute(QLatin1String("xmlns"), nsUri);
}

void ESoapElement::setESoapNamespaces(const ESoapNamespaces::Ptr &namespaces)
{
    m_namespaces = namespaces;
}

ESoapElement ESoapElement::firstChildTypedElement(const QString &name, const QString &nsUri) const
{
    QString prefix = m_namespaces->prefixFor(nsUri);
    ESoapElement element = firstChildElement(prefix % QLatin1Char(':') % name);
    element.setESoapNamespaces(m_namespaces);
    return element;
}

ESoapElement ESoapElement::firstChildElement(const QString &tagName) const
{
    ESoapElement element = QDomElement::firstChildElement(tagName);
    element.setESoapNamespaces(m_namespaces);
    return element;
}

ESoapElement ESoapElement::nextSiblingElement(const QString &tagName) const
{
    ESoapElement element = QDomElement::nextSiblingElement(tagName);
    element.setESoapNamespaces(m_namespaces);
    return element;
}

QString ESoapElement::findParentNamespace(const QDomNode &parent, const QString &prefix)
{
    if (parent.isNull()) {
        return QString();
    }

//    qDebug() << Q_FUNC_INFO << "looking for prefix" << prefix << parent.nodeName();
    if (parent.prefix() == prefix && !parent.namespaceURI().isEmpty()) {
//        qDebug() << Q_FUNC_INFO << "found prefix:" << parent.prefix() << parent.namespaceURI();
        return parent.namespaceURI();
    }

    QString nodeName = QLatin1String("xmlns:") % prefix;
    QDomNamedNodeMap map = parent.attributes();
    for (int i = 0; i < map.length(); ++i) {
        QDomNode node = map.item(i);
        if (node.toAttr().nodeName() == nodeName) {
//            qDebug() << Q_FUNC_INFO << "found prefix:"  << prefix << parent.nodeName();
            return node.toAttr().nodeValue();
        }
//        qDebug() << Q_FUNC_INFO << " nodes:"  << node.toAttr().nodeName() << node.nodeName();
    }

    return findParentNamespace(parent.parentNode(), prefix);
}
