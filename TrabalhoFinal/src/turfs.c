#include "globals.h"

void turf_set_pos(pTurf T, float a, float b){
    T->pos.x = a;
    T->pos.y = b;
}

pTurf get_turf(Vector2 coord){
    return &pMAP_ACESS_TURF(cur_map, (int)coord.x, (int)coord.y);
}

int can_move(pMob to_move, pTurf dest){
    if(dest->solid){
        return 0;
    }
    return 1;
}
