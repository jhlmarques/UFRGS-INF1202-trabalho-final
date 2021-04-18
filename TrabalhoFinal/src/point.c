#include "point.h"
#include "defines.h"

void point_move_dir(pPoint P, int dir){
    switch(dir){
        case NORTH:
        P->y += 1;
        break;
        case EAST:
        P->x += 1;
        break;
        case SOUTH:
        P->y -= 1;
        break;
        case WEST:
        P->x -= 1;
        break;

    }

}
