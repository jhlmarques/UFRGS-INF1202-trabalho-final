#include "items.h"
#include "turfs.h"
#include "globals.h"
#include "game.h"


pItem GetItem(int item_id){
    return &cur_map->items[item_id];
}

void ItemTouched(int item_id){
    pItem I = GetItem(item_id);
    switch(I->type){
        case ITEM_POWER:
        OnPlayerCollectPower();
        GetTurf(I->pos)->cur_item = NO_ID;//Sai do mapa
        break;
        case ITEM_WATER:
        OnPlayerKilled();
        break;
        case ITEM_KEY:
        OnKeyCollected();
        break;
        case ITEM_EXIT:
        OnLevelEnd();
        break;
    }
}

void SetItemPos(pItem I, int x, int y){
    I->pos.x = x;
    I->pos.y = y;
    pTurf T = GetTurf(I->pos);
    T->cur_item = I->id;
}
