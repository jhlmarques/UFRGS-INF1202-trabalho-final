#include "globals.h"

void TurfSetPos(pTurf T, float a, float b){
    T->pos.x = a;
    T->pos.y = b;
}

pTurf GetTurf(Vector2 coord){
    return &pMAP_ACESS_TURF(cur_map, (int)coord.x, (int)coord.y);
}


