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
#include <QSharedDataPointer>

namespace Ews {

class EffectiveRightsPrivate;
class EWS_EXPORT EffectiveRights
{
public:
    bool canCreateAssociated() const;
    bool canCreateContents() const;
    bool canCreateHierarchy() const;
    bool canDelete() const;
    bool canModify() const;
    bool canRead() const;

    EffectiveRights();
    virtual ~EffectiveRights();

public:
    EffectiveRights(const EffectiveRights &);
    EffectiveRights &operator=(const EffectiveRights &);

protected:
    friend class FolderPrivate;
    EffectiveRights(EffectiveRightsPrivate &d);
    QSharedDataPointer<EffectiveRightsPrivate> d_ptr;

protected:
    // Q_DECLARE_PRIVATE equivalent for shared data pointers
    EffectiveRightsPrivate* d_func();
    inline const EffectiveRightsPrivate* d_func() const
    {
        return d_ptr.constData();
    }
};

}

#endif // EWSEFFECTIVERIGHTS_H
