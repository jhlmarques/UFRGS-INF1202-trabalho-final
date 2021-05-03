#ifndef _save_states_h_
#define _save_states_h_

#include "defines.h"

typedef struct save_state{
    unsigned int save_id; //Identificador da gravação
    unsigned int points; //Pontos acumulados
    unsigned int lives; //Vidas
    unsigned int cur_level; //Nível atual
    char player_name[PLAYER_NAME_LEN]; //Nome do jogador

}save_state, *pSave_state;

int Savefile_SavesAmnt(char* savefile_name);

int LoadSaveFile(char* savefile_name, pSave_state saves_v);

int WriteSaveToFile(char* savefile_name, pSave_state save_to_write, int pos);

void NewSaveState(pSave_state save, char* p_name);

void DeleteSave(char* savefile_name, int pos);

#endif
