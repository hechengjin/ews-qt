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

#ifndef ESOAPMESSAGE_H
#define ESOAPMESSAGE_H

#include "export.h"
#include "esoapelement.h"
#include "esoapnamespaces.h"

#include <QDomDocument>
#include <QHash>

#define EWS_TYPES_NS    "http://schemas.microsoft.com/exchange/services/2006/types"
#define EWS_MESSAGES_NS "http://schemas.microsoft.com/exchange/services/2006/messages"

class EWS_EXPORT ESoapMessage : public QDomDocument
{
public:
    ESoapMessage();
    ESoapMessage(const QDomDocument &other);

    void print();
    bool parserError();

    ESoapElement envelope() const;
    ESoapElement header();
    ESoapElement body();

    ESoapElement createElement(const QString &name);
    ESoapElement createTypedElement(const QString &name, const QString &nsUri);
    ESoapElement createTypedHeaderElement(const QString &name, const QString &nsUri);

protected:
    void extractNamespaces(const QDomElement &element);

    ESoapElement m_envelope;
    ESoapElement m_header;
    ESoapElement m_body;
    ESoapNamespaces::Ptr m_namespaces;
    bool m_parserError;
};

#endif // ESOAPMESSAGE_H
