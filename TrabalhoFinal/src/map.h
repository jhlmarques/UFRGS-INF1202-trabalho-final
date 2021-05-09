#ifndef _map_h_
#define _map_h_

#include "mobs.h"
#include "items.h"
#include "turfs.h"

//DEFINIÇÕES PARA MODO GRÁFICO ASCII
#define ASCII_TURF_EMPTY ' '
#define ASCII_TURF_SOLID 'P'
#define ASCII_TURF_HAS_PLAYER '@'
#define ASCII_TURF_HAS_FRIENDLY 'F'
#define ASCII_TURF_HAS_HOSTILE 'E'
#define ASCII_TURF_HAS_NEUTRAL 'B'
#define ASCII_TURF_HAS_KEY 'C'
#define ASCII_TURF_HAS_WATER 'A'
#define ASCII_TURF_HAS_DOOR 'T'
#define ASCII_TURF_HAS_MOBANDITEM 'X'

#define pMAP_ACESS_TURF(map, x, y) (map->turfs[y * map->bounds_x + x]) //Acessa o territorio na coordenada x,y do mapa
#define CHAR2MOB_I(c) (c - 'a' + 1) //1 - 27; A criatura na posição 0 sempre é o jogador

//Mapa
typedef struct game_map{
    pMob mobs; //Criaturas no mapa
    pItem items; //Itens no mapa
    pTurf turfs; //Vetor de chaos/paredes no mapa, acessado como matriz pelo macro pMAP_ACESS_TURF(mapa, linha, coluna)
    pMob_movement movement_patterns; //Padrões de movimento do mapa
    Vector2 player_start_pos; //Posicão de inicio do jogador
    int n_mobs; //Total de criaturas
    int n_items; //Total de items
    int n_mpatterns; //Total de padroes de movimento
    int bounds_x; //Limite x
    int bounds_y; //Limite y
    int enemies_left; //Numero de inimigos restantes
    int points; //Pontos acumulados (não gravados até o fim do mapa)
}game_map, *pGame_map;


//Mostra o mapa no prompt de comando (graficos ASCII)
void PrintMap_ASCII(pGame_map map);

//Converte uma string para uma direção (definidas em define.h)
int StrToDir(char* str);

//Cria o vetor de criaturas do mapa
void MapCreateMobV(pGame_map map, int amount);

//Cria o vetor de itens do mapa
void MapCreateItemV(pGame_map map, int amount);

//Cria o vetor de territorios do mapa e as define minimamente
void MapCreateTurfs(pGame_map map);

//Cria o vetor de padrões de movimento do mapa
void MapCreateMovementPatternV(pGame_map map, int amount);

//Libera os elementos alocados dinamicamente do mapa
void MapFreeElements(pGame_map map);

//Define e/ou aloca os elementos de um mapa
void SetMap(pGame_map map, int bx, int by, int nm, int ni, int np, int nenemies);

//Carrega o arquivo de tipos de criaturas
int LoadMobTypes(char* filename);

//Carrega um arquivo de texto e o lê para popular o mapa
int PopulateMap(char* filename, pGame_map map);

//Popula o mapa atual lendo um dos mapas do arquivo contendo os caminhos para os mapas
int PopulateCurMapFromMapList(char* map_list_file, int index);

#endif


