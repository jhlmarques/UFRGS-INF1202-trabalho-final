#ifndef _mobs_h_
#define _mobs_h_

#include "mob_movement.h"
#include "turfs.h"
#include "defines.h"
#include "raylib.h"

typedef struct mob{
    int health; //Vida; para toda criatura, vida <= 0 significa que esta n�o interage
    int invincible; //Nao pode ter sua vida reduzida
    int dir; //Direção do movimento
    pMob_movement movement; //Se n�o for um ponteiro nulo, define o movimento
    Vector2 pos; //Posi��o atual.
    /* int icon; //Imagem atual */
    int faction; //Amigo, inimigo, neutro
    int id; //Identificador �nico
    int type_id; //Identificador do tipo de criatura
}mob, *pMob;

#define pMOB_IS_PLAYER(pMob) (pMob->id == PLAYER_ID)

int is_alive(pMob mob);


int can_attack(pMob mob);

int push(pMob moved, int direction);

int attack(pMob attacker, pMob attacked);

void simple_move(pMob moved, pTurf dest);

int move_check_interactions(pMob moved);

void set_mob_pos(pMob M, int x, int y);

#endif
