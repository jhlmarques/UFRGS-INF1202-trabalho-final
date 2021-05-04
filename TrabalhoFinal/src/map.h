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
#define CHAR2MOB_I(c) (c - 'a' + 1) //1 - 27; A criatura na posição 0 sempre é o jogador

//Mapa
typedef struct game_map{
    pMob mobs; //Criaturas no mapa
    pItem items; //Itens no mapa
    pTurf turfs; //Vetor de chaos/paredes no mapa, acessado como matriz pelo macro pMAP_ACESS_TURF(mapa, linha, coluna)
    pMob_movement movement_patterns; //Padrões de movimento do mapa
    unsigned int n_mobs; //Total de criaturas
    unsigned int n_items; //Total de items
    unsigned int n_mpatterns; //Total de padroes de movimento
    unsigned int bounds_x; //Limite x
    unsigned int bounds_y; //Limite y
    int current_signals; //Sinais enviados por items no mapa (exemplo: chave consumida, jogador morto, etc)
}game_map, *pGame_map;


//Função para debug
void PrintMap_ASCII(pGame_map map);

int StrToDir(char* str);

void MapCreateMobV(pGame_map map, int amount);

void MapCreateItemV(pGame_map map, int amount);

void MapCreateTurfs(pGame_map map);

void MapCreateMovementPatterns(pGame_map map, int amount);

void MapFreeMap(pGame_map map);

void MapCreateMap(pGame_map map, int bx, int by, int nm, int ni, int np);

int LoadMobTypes(char* filename);

int LoadMap(char* filename, pGame_map map);

#endif


