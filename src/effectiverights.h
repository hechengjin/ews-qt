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

#include "export.h"

#include <QObject>

namespace Ews {

class EffectiveRightsPrivate;
class EWS_EXPORT EffectiveRights
{
    Q_GADGET
    Q_DECLARE_PRIVATE(EffectiveRights)
public:
    EffectiveRights();
    EffectiveRights(EffectiveRightsPrivate *priv);
    virtual ~EffectiveRights();

    bool canCreateAssociated() const;
    bool canCreateContents() const;
    bool canCreateHierarchy() const;
    bool canDelete() const;
    bool canModify() const;
    bool canRead() const;

private:
    EffectiveRightsPrivate *d_ptr;
};

}

#endif // EWSEFFECTIVERIGHTS_H
