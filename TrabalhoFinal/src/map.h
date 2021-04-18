#ifndef _map_h_
#define _map_h_

#include "mobs.h"
#include "items.h"
#include "turfs.h"

#define ASCII_TURF_EMPTY ','
#define ASCII_TURF_SOLID '#'
#define ASCII_TURF_HAS_MOB 'M'
#define ASCII_TURF_HAS_ITEM 'I'
#define ASCII_TURF_HAS_MOBANDITEM '@'

#define pMAP_ACESS_TURF(map, x, y) (map->turfs[y * map->bounds_x + x])


//Mapa
typedef struct game_map{
    pMob mobs; //Criaturas no mapa
    pItem items; //Itens no mapa
    pTurf turfs; //Vetor de chaos/paredes no mapa, acessado como matriz pelo macro pMAP_ACESS_TURF(mapa, linha, coluna)
    unsigned int n_mobs; //Total de criaturas
    unsigned int n_items; //Total de items
    unsigned int bounds_x; //Limite x
    unsigned int bounds_y; //Limite y
    int current_signals; //Sinais enviados por items no mapa (exemplo: chave consumida, jogador morto, etc)
}game_map, *pGame_map;

void print_map_ASCII(pGame_map map);

void map_free_mobs(pGame_map map);

void map_create_mob_v(pGame_map map, int amount);

void map_free_items(pGame_map map);

void map_create_item_v(pGame_map map, int amount);

void map_create_turfs(pGame_map map);

void map_free_map(pGame_map map);

void map_create_map(pGame_map map, int bx, int by, int nm, int ni);

#endif
