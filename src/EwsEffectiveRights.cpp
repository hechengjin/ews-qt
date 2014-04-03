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

using namespace Ews;

EffectiveRights::EffectiveRights() :
    d_ptr(0)
{

}

EffectiveRights::EffectiveRights(EffectiveRightsPrivate *priv) :
    d_ptr(priv)
{
}

EffectiveRights::~EffectiveRights()
{
    delete d_ptr;
}

bool EffectiveRights::canCreateAssociated() const
{
    Q_D(const EffectiveRights);
    return d->rights.createAssociated();
}

bool EffectiveRights::canCreateContents() const
{
    Q_D(const EffectiveRights);
    return d->rights.createContents();
}

bool EffectiveRights::canCreateHierarchy() const
{
    Q_D(const EffectiveRights);
    return d->rights.createHierarchy();
}

bool EffectiveRights::canDelete() const
{
    Q_D(const EffectiveRights);
    return d->rights.delete_();
}

bool EffectiveRights::canModify() const
{
    Q_D(const EffectiveRights);
    return d->rights.modify();
}

bool EffectiveRights::canRead() const
{
    Q_D(const EffectiveRights);
    return d->rights.read();
}


EffectiveRightsPrivate::EffectiveRightsPrivate(const T__EffectiveRightsType &effectiveRights) :
    rights(effectiveRights)
{

}
