#ifndef _point_h_
#define _point_h_

typedef struct point{
    unsigned int x;
    unsigned int y;
}point, *pPoint;

void point_move_dir(pPoint P, int dir);

#endif