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

//Retorna a quantidade de gravações encontradas em um arquivo de gravações
int Savefile_SavesAmnt(char* savefile_name);

//Carrega um vetor de gravações de um arquivo de gravações
int LoadSaveFile(char* savefile_name, pSave_state saves_v);

//Guarda uma gravação numa determinada posição dum arquivo de gravações
int WriteSaveToFile(char* savefile_name, pSave_state save_to_write, int pos);

//Define uma gravação como uma vazia
void NewSaveState(pSave_state save, char* p_name, int id);

//Deleta uma gravação dum arquivo de gravações
void DeleteSaveFromFile(char* savefile_name, int pos);

#endif
