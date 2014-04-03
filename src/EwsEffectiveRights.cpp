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

#include "EwsEffectiveRights_p.h"
#include "EwsRequest.h"

EwsEffectiveRights::EwsEffectiveRights() :
    d_ptr(0)
{

}

EwsEffectiveRights::EwsEffectiveRights(EwsEffectiveRightsPrivate *priv) :
    d_ptr(priv)
{
}

EwsEffectiveRights::~EwsEffectiveRights()
{
    delete d_ptr;
}

bool EwsEffectiveRights::canCreateAssociated() const
{
    Q_D(const EwsEffectiveRights);
    return d->rights.createAssociated();
}

bool EwsEffectiveRights::canCreateContents() const
{
    Q_D(const EwsEffectiveRights);
    return d->rights.createContents();
}

bool EwsEffectiveRights::canCreateHierarchy() const
{
    Q_D(const EwsEffectiveRights);
    return d->rights.createHierarchy();
}

bool EwsEffectiveRights::canDelete() const
{
    Q_D(const EwsEffectiveRights);
    return d->rights.delete_();
}

bool EwsEffectiveRights::canModify() const
{
    Q_D(const EwsEffectiveRights);
    return d->rights.modify();
}

bool EwsEffectiveRights::canRead() const
{
    Q_D(const EwsEffectiveRights);
    return d->rights.read();
}


EwsEffectiveRightsPrivate::EwsEffectiveRightsPrivate(const T__EffectiveRightsType &effectiveRights) :
    rights(effectiveRights)
{

}
