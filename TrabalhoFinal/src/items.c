#include "items.h"
#include "turfs.h"


void ItemActivated(int item_id){
    return;
}

void SetItemPos(pItem I, int x, int y){
    I->pos.x = x;
    I->pos.y = y;
    pTurf T = GetTurf(I->pos);
    T->cur_item = I->id;
}
