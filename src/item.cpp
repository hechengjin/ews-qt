#include "item_p.h"

using namespace Ews;

Item::Item()
    : d_ptr(new ItemPrivate)
{
}

Item::~Item()
{

}

Item::Item(const Item &)
{

}

Item &Item::operator=(const Item &item)
{
    d_ptr = item.d_ptr;
    return *this;
}

void Item::setSubject(const QString &subject)
{
    d_ptr->item.setSubject(subject);
}


ItemPrivate::ItemPrivate()
{

}

ItemPrivate::ItemPrivate(T__ItemType itemType)
{
    item = itemType;
}


Ews::Item::Item(Ews::ItemPrivate &d)
    : d_ptr(&d)
{

}
