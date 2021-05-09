
#ifndef _globals_h_
#define _globals_h_

//Variaveis globais
//Definidas em main.c
#include "defines.h"
#include "map.h"
#include "save_states.h"

extern pGame_map cur_map; //Mapa atual
extern pSave_state cur_save; //Gravação atual
extern Texture2D * all_textures; //Vetor de texturas (Raylib)
extern int texture_amount; //Quantidade de texturas carregadas
extern Texture2D base_mob_texture; //Texturas básicas, na ausência de texturas
extern Texture2D base_item_texture;
extern Texture2D base_turf_texture;
extern save_state all_saves[MAX_SAVES]; //Vetor de gravações
extern int saves_loaded; //Última quantidade de gravações lidas
extern pMob mob_types; //Vetor com todos TIPOS de criatura
extern int mob_type_amount; //Tamanho do vetor acima
extern int game_state; //Estado do jogo 
extern pMob player_mob; //Criatura controlada pelo jogador

#endif

