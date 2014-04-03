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
