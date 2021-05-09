#ifndef _mobs_h_
#define _mobs_h_

//Para lidar com referência circular
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
    int texture; //Imagem atual
    int faction; //Amigo, inimigo, neutro
    int id; //Identificador �nico
}mob, *pMob;

#define pMOB_IS_PLAYER(pMob) (pMob->id == PLAYER_ID) //Checa se a criatura é a controlada pelo jogador

//A criatura está viva?
int IsAlive(pMob mob);

//Acessa o mapa atual e retorna a criatura de id igual ao fornecido
pMob GetMob(int mob_id);

//Checa se uma criatura pode atacar a outra
int CanAttack(pMob attacker, pMob attacked);

//Lida com uma criatura tentando empurrar outra
int Push(pMob moved, int direction);

//Lógica após uma criatura ser atacada por outra
void OnAttacked(pMob Attacked);

//Lida com uma tentativa de ataque de uma criatura
int Attack(pMob Attacker, pMob Attacked);

//Move uma criatura de um território para outro
void SimpleMove(pMob moved, pTurf dest);

//Tenta mover uma criatura, checando colisões
int MoveCheckInteractions(pMob moved);

//Põe uma criatura no território de posição x,y do mapa
void SetMobPos(pMob M, int x, int y);

//Definições básicas de uma criatura
void SetBasicMob(pMob M, int health, int texture, int faction);

#endif
