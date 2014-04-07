#ifndef ITEM_P_H
#define ITEM_P_H

#include "item.h"
#include "wsdl_Services.h"

namespace Ews {

class ItemPrivate : public QSharedData
{
public:
    ItemPrivate();
    ItemPrivate(T__ItemType itemType);

    T__ItemType item;
};

}

#endif // ITEM_P_H
