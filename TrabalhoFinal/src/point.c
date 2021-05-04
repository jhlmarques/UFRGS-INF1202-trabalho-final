#include "point.h"
#include "defines.h"

Vector2 PointMoveDir(Vector2 P, int dir){
    switch(dir){
        case NORTH:
            P.y -= 1.0f;
            return P;
            break;
        case EAST:
            P.x += 1.0f;
            return P;
            break;
        case SOUTH:
            P.y += 1.0f;
            return P;
            break;
        case WEST:
            P.x -= 1.0f;
            return P;
            break;

    }
    return P;
}
