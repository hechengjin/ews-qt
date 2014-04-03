#ifndef EWSEFFECTIVERIGHTS_P_H
#define EWSEFFECTIVERIGHTS_P_H

#include "EwsEffectiveRights.h"
#include "wsdl_Services.h"

class EwsEffectiveRightsPrivate
{
public:
    EwsEffectiveRightsPrivate(const T__EffectiveRightsType &effectiveRights);

    T__EffectiveRightsType rights;
};

#endif // EWSEFFECTIVERIGHTS_P_H
