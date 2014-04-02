/*
 * Copyright (C) 2013 Daniel Nicoletti <dantti12@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 */

#include "EwsEffectiveRights.h"
#include "EwsRequest.h"

EwsEffectiveRights::EwsEffectiveRights()
{
}

//EwsEffectiveRights::EwsEffectiveRights(const ESoapElement &emailAddressElement)
//{
//    ESoapElement element;

//    element = emailAddressElement.firstChildElement();
//    while (!element.isNull()) {
//        if (element.equalNS(QLatin1String("CreateAssociated"), EWS_TYPES_NS)) {
//            m_canCreateAssociated = element.text() == QLatin1String("true");
//        } else if (element.equalNS(QLatin1String("CreateContents"), EWS_TYPES_NS)) {
//            m_canCreateContents = element.text() == QLatin1String("true");
//        } else if (element.equalNS(QLatin1String("CreateHierarchy"), EWS_TYPES_NS)) {
//            m_canCreateHierarchy = element.text() == QLatin1String("true");
//        } else if (element.equalNS(QLatin1String("Delete"), EWS_TYPES_NS)) {
//            m_canDelete = element.text() == QLatin1String("true");
//        } else if (element.equalNS(QLatin1String("Modify"), EWS_TYPES_NS)) {
//            m_canModify = element.text() == QLatin1String("true");
//        } else if (element.equalNS(QLatin1String("Read"), EWS_TYPES_NS)) {
//            m_canRead = element.text() == QLatin1String("true");
//        }

//        element = element.nextSiblingElement();
//    }
//}

bool EwsEffectiveRights::canCreateAssociated() const
{
    return m_canCreateAssociated;
}

bool EwsEffectiveRights::canCreateContents() const
{
    return m_canCreateContents;
}

bool EwsEffectiveRights::canCreateHierarchy() const
{
    return m_canCreateHierarchy;
}

bool EwsEffectiveRights::canDelete() const
{
    return m_canDelete;
}

bool EwsEffectiveRights::canModify() const
{
    return m_canModify;
}

bool EwsEffectiveRights::canRead() const
{
    return m_canRead;
}
