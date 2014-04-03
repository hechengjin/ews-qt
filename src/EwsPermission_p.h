#ifndef EWSPERMISSION_P_H
#define EWSPERMISSION_P_H

#include "EwsPermission.h"
#include "wsdl_Services.h"

class EwsPermissionPrivate
{
public:
    EwsPermissionPrivate(const T__PermissionType &permissionType);

    T__PermissionType permission;
};

#endif // EWSPERMISSION_P_H
