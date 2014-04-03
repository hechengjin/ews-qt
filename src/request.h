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

#ifndef EWSREQUEST_H
#define EWSREQUEST_H

#include <QObject>
#include <QDomDocument>
#include <QUrl>

#include "export.h"
#include "esoapmessage.h"

namespace Ews {

class EWS_EXPORT Request : public ESoapMessage
{
    Q_GADGET
    Q_ENUMS(ServerVersion)
public:
    enum ServerVersion {
        Exchange2007,
        Exchange2007_SP1,
        Exchange2010,
        Exchange2010_SP1,
        Exchange2010_SP2
    };
    Request(const QDomDocument &document);
    Request(const QString &method,
               ServerVersion version);

    static QDomDocument autoDiscover(const QString &emailAddress);

    ESoapElement method() const;
    QString methodName() const;

private:
    void init(ServerVersion version);
//    ESoapElement createMethod(const QString &method);
    ESoapElement m_method;
};

}

#endif // EWSREQUEST_H
