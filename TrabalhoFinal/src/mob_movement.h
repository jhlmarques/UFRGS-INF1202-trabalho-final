#ifndef _mob_movement_h_
#define _mob_movement_h_

#include "point.h"

typedef struct mob_movement{
    int movement_interval; //Quantos movimentos do jogador at� essa criatura se mover
    pPoint cur_destination; //Ponto ao qual a criatura est� se movendo
    int flags;

}mob_movement, *pMob_movement;

#endif