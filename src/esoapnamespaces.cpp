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

#include "esoapnamespaces.h"
#include <QDebug>

ESoapNamespaces::ESoapNamespaces()
{
}

void ESoapNamespaces::registerNamespace(const QString &prefix, const QString &uri)
{
    m_namespaces.insert(uri, prefix);
}

QString ESoapNamespaces::prefixFor(const QString &ns)
{
    if (!m_namespaces.contains(ns)) {
        qWarning() << Q_FUNC_INFO << "namespace NOT found" << ns;
    }
    return m_namespaces.value(ns);
}

ESoapNamespaces::Ptr &ESoapNamespaces::instance()
{
    static ESoapNamespaces::Ptr esoapNamespaces(new ESoapNamespaces());
    return esoapNamespaces;
}
