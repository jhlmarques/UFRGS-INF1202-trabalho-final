#ifndef _mob_movement_h_
#define _mob_movement_h_

#include "raylib.h"
#include "defines.h"

typedef struct movement_command{ //Estrutura guardando uma direção e uma quantidade de passos
    int dir; //Direção a se mover
    int amount; //Quantos passos nessa direção
}movement_command, *pMovement_command;

typedef struct mob_movement{ //Define uma sequência de movimentos a serem executados em loop infinito
    int movement_interval; //Quantos movimentos do jogador at� essa criatura se mover
    int command_amnt; //Quantidade de comandos
    movement_command commands[MAX_MOVEMENT_COMMANDS];//Comandos
}mob_movement, *pMob_movement;

#endif
