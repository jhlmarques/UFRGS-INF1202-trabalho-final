#ifndef _map_h_
#define _map_h_

#include "mobs.h"
#include "items.h"
#include "turfs.h"

//Mapa
typedef struct game_map{
    pMob mobs; //Criaturas no mapa
    pItem items; //Itens no mapa
    pTurf* turfs; //Matriz de chaos/paredes no mapa
    unsigned int bounds_x; //Limite x
    unsigned int bounds_y; //Limite y
    int current_signals; //Sinais enviados por items no mapa (exemplo: chave consumida, jogador morto, etc)
}game_map, *pGame_map;

#endif
