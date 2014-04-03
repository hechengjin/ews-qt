/*
 * Copyright (C) 2013-2014 Daniel Nicoletti <dantti12@gmail.com>
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

#ifndef EWSPERMISSION_P_H
#define EWSPERMISSION_P_H

#include "permission.h"
#include "wsdl_Services.h"

namespace Ews {

class PermissionPrivate
{
public:
    PermissionPrivate(const T__PermissionType &permissionType);

    T__PermissionType permission;
};

}

#endif // EWSPERMISSION_P_H
