#ifndef _mob_movement_h_
#define _mob_movement_h_

#include "raylib.h"
#include "defines.h"

typedef struct movement_command{ //Estrutura guardando uma direção e uma quantidade de passos
    int dir;
    int amount;
}movement_command, *pMovement_command;

typedef struct mob_movement{
    int movement_interval; //Quantos movimentos do jogador at� essa criatura se mover
    int command_amnt; //Quantidade de comandos
    movement_command commands[MAX_MOVEMENT_COMMANDS];
    int steps_left; //Passos até a leitura do proximo comando
    int type;

}mob_movement, *pMob_movement;

#endif
