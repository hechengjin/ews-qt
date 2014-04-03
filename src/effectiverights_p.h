#ifndef EWSEFFECTIVERIGHTS_P_H
#define EWSEFFECTIVERIGHTS_P_H

#include "effectiverights.h"
#include "wsdl_Services.h"

namespace Ews {

class EffectiveRightsPrivate
{
public:
    EffectiveRightsPrivate(const T__EffectiveRightsType &effectiveRights);

    T__EffectiveRightsType rights;
};

}

#endif // EWSEFFECTIVERIGHTS_P_H
