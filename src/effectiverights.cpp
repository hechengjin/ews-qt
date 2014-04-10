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

#include "effectiverights_p.h"
#include "request.h"

using namespace Ews;

EffectiveRights::EffectiveRights()
    : d_ptr(new EffectiveRightsPrivate)
{

}

EffectiveRights::~EffectiveRights()
{
}

EffectiveRights::EffectiveRights(const EffectiveRights &other)
    : d_ptr(other.d_ptr)
{

}

EffectiveRights &EffectiveRights::operator=(const EffectiveRights &other)
{
    d_ptr = other.d_ptr;
    return *this;
}

EffectiveRights::EffectiveRights(EffectiveRightsPrivate &d)
    : d_ptr(&d)
{

}

EffectiveRightsPrivate *EffectiveRights::d_func()
{
    return d_ptr.data();
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


EffectiveRightsPrivate::EffectiveRightsPrivate()
{

}

EffectiveRightsPrivate::EffectiveRightsPrivate(const T__EffectiveRightsType &effectiveRights) :
    rights(effectiveRights)
{

}
