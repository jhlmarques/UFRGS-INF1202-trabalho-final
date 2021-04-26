
#ifndef _globals_h_
#define _globals_h_

//Variaveis globais
//Definidas em main.c
#include "defines.h"
#include "map.h"
#include "save_states.h"

extern pGame_map cur_map; //Mapa atual
extern pSave_state cur_save; //Gravação atual
extern save_state all_saves[MAX_SAVES]; //Vetor de gravações
extern int saves_loaded; //Última quantidade de gravações lidas


#endif

