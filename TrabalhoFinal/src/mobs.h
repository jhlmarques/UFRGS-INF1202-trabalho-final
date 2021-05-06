#ifndef _mobs_h_
#define _mobs_h_

typedef struct turf *pTurf;

#include "mob_movement.h"
#include "turfs.h"
#include "defines.h"
#include "raylib.h"

typedef struct mob{
    int health; //Vida; para toda criatura, vida <= 0 significa que esta n�o interage
    int powered; //Se ligado, ganha das outras facções não-neutras
    int dir; //Direção do movimento
    int movement_pattern; //Se menor que zero, não segue um padrão de movimento
    int cur_movement_command;//Posicao do atual comando de movimento no vetor do padrão de movimento ligado a essa criatura
    int movement_counter; //Incrementado a cada movimento, resetado por outras funções 
    int action_cooldown;//Frames ate a proxima ação
    Vector2 pos; //Posi��o atual.
    int icon; //Imagem atual
    int faction; //Amigo, inimigo, neutro
    int id; //Identificador �nico
}mob, *pMob;

#define pMOB_IS_PLAYER(pMob) (pMob->id == PLAYER_ID)

int IsAlive(pMob mob);


pMob GetMob(int mob_id);

int CanAttack(pMob attacker, pMob attacked);

int Push(pMob moved, int direction);

void OnAttacked(pMob Attacked);

int Attack(pMob Attacker, pMob Attacked);

void SimpleMove(pMob moved, pTurf dest);

int MoveCheckInteractions(pMob moved);

void SetMobPos(pMob M, int x, int y);

void SetBasicMob(pMob M, int health, int icon, int faction);

#endif
