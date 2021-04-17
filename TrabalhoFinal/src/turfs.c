#include "globals.h"

pTurf get_turf(pPoint coord){
    return &cur_map->turfs[coord->x][coord->y];
}

int can_move(pMob to_move, pTurf dest){
    if(dest->solid){
        return 0;
    }
    return 1;
}