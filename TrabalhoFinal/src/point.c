#include "point.h"
#include "defines.h"

void point_move_dir(Vector2 P, int dir){
    switch(dir){
        case NORTH:
        P.y -= 1.0f;
        break;
        case EAST:
        P.x += 1.0f;
        break;
        case SOUTH:
        P.y += 1.0f;
        break;
        case WEST:
        P.x -= 1.0f;
        break;

    }

}
