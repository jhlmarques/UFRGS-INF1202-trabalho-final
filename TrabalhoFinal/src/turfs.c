#include "globals.h"

void turf_set_pos(pTurf T, int x, int y){
    T->pos.x = x;
    T->pos.y = y;
}

pTurf get_turf(pPoint coord){
    return &pMAP_ACESS_TURF(cur_map, coord->x, coord->y);
}

int can_move(pMob to_move, pTurf dest){
    if(dest->solid){
        return 0;
    }
    return 1;
}