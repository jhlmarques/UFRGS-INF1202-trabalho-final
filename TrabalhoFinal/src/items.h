#ifndef _items_h_
#define _items_h_

#include "point.h"
#include "raylib.h"

typedef struct item{
    Vector2 pos;
    int id;

}item, *pItem;

void ItemActivated(int item_id);

void SetItemPos(pItem I, int x, int y);

#endif
