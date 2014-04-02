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

#ifndef ESOAPELEMENT_H
#define ESOAPELEMENT_H

#include "ewsexport.h"
#include "ESoapNamespaces.h"

#include <QDomElement>
#include <QHash>

class EWS_EXPORT ESoapElement : public QDomElement
{
public:
    ESoapElement();
    ESoapElement(const ESoapNamespaces::Ptr &namespaces);
    ESoapElement(const QDomElement &other);

    bool equalNS(const QString &name, const QString &nsUri) const;

    QDomNode appendChild(const ESoapElement &newChild);
    void setPrefixNS(const QString &prefix, const QString &nsUri);
    void setText(const QString &text);
    QString prefix() const;
    QString nsUri() const;
    void addNamespace(const QString &nsUri);
    void setDefaultNamespace(const QString &nsUri);
    void setESoapNamespaces(const ESoapNamespaces::Ptr &namespaces);

    ESoapElement firstChildTypedElement(const QString &name, const QString &nsUri) const;
    ESoapElement firstChildElement(const QString &tagName = QString()) const;
    ESoapElement nextSiblingElement(const QString &tagName = QString()) const;

private:
    QString findParentNamespace(const QDomNode &parent, const QString &prefix);
    QString m_prefix;
    QString m_nsUri;
    ESoapNamespaces::Ptr m_namespaces;
};

#endif // ESOAPELEMENT_H
