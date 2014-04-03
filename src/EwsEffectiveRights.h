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

#include <QObject>

class EwsEffectiveRightsPrivate;
class EWS_EXPORT EwsEffectiveRights
{
    Q_GADGET
    Q_DECLARE_PRIVATE(EwsEffectiveRights)
public:
    EwsEffectiveRights();
    EwsEffectiveRights(EwsEffectiveRightsPrivate *priv);
    virtual ~EwsEffectiveRights();

    bool canCreateAssociated() const;
    bool canCreateContents() const;
    bool canCreateHierarchy() const;
    bool canDelete() const;
    bool canModify() const;
    bool canRead() const;

private:
    EwsEffectiveRightsPrivate *d_ptr;
};

#endif // EWSEFFECTIVERIGHTS_H
