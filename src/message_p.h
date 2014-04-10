#ifndef MESSAGE_P_H
#define MESSAGE_P_H

#include "item_p.h"
#include "message.h"
//#include "effectiverights.h"

#include "wsdl_Services.h"

namespace Ews {

class MessagePrivate : public ItemPrivate
{
public:
    MessagePrivate();
    MessagePrivate(const T__MessageType &itemType);

    T__MessageType message;
//    EffectiveRights m_effectiveRights;
};

}

#endif // MESSAGE_P_H
