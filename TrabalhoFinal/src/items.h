#ifndef _items_h_
#define _items_h_

#include "point.h"

typedef struct item{
    point pos;
    int id;

}item, *pItem;

void item_activated(int item_id);

#endif