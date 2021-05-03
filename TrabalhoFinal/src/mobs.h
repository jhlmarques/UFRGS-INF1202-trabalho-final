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
    int icon; //Imagem atual
    int faction; //Amigo, inimigo, neutro
    int id; //Identificador �nico
    int type_id; //Identificador do tipo de criatura
}mob, *pMob;

#define pMOB_IS_PLAYER(pMob) (pMob->id == PLAYER_ID)

int IsAlive(pMob mob);


int CanAttack(pMob mob);

int Push(pMob moved, int direction);

int Attack(pMob Attacker, pMob Attacked);

void SimpleMove(pMob moved, pTurf dest);

int MoveCheckInteractions(pMob moved);

void SetMobPos(pMob M, int x, int y);

#endif
