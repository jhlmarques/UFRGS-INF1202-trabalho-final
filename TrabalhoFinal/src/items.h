#ifndef _items_h_
#define _items_h_

#include "point.h"
#include "raylib.h"

typedef struct item{
    Vector2 pos;
    int id;

}item, *pItem;

void item_activated(int item_id);

#endif
