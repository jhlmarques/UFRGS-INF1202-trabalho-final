#ifndef _items_h_
#define _items_h_

#include "point.h"
#include "raylib.h"

typedef struct item{
    Vector2 pos; //Posição
    int type; //Tipo de item
    int id; //Identificador

}item, *pItem;

pItem GetItem(int item_id);

void ItemTouched(int item_id);

void SetItemPos(pItem I, int x, int y);

#endif
