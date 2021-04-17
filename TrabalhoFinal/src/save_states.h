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

#endif
