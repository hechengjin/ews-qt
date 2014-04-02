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

#ifndef EWSEFFECTIVERIGHTS_H
#define EWSEFFECTIVERIGHTS_H

#include "ewsexport.h"
//#include "ESoapElement.h"

class EWS_EXPORT EwsEffectiveRights
{
public:
    EwsEffectiveRights();
//    EwsEffectiveRights(/*const ESoapElement &emailAddressElement*/);

    bool canCreateAssociated() const;
    bool canCreateContents() const;
    bool canCreateHierarchy() const;
    bool canDelete() const;
    bool canModify() const;
    bool canRead() const;

private:
    bool m_canCreateAssociated;
    bool m_canCreateContents;
    bool m_canCreateHierarchy;
    bool m_canDelete;
    bool m_canModify;
    bool m_canRead;
};

#endif // EWSEFFECTIVERIGHTS_H
