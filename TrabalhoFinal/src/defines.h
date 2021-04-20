#ifndef _defines_h_
#define _defines_h_

#include <stddef.h>

//Fac��es
#define NEUTRAL 0
#define FRIENDLY 1
#define HOSTILE 2

#define PLAYER_ID 0
#define NO_ID -1

#define MOVEMENT_BOUNCE (1<<0) //Ao atingir uma parede, se move na dire��o oposta

#define PLAYER_NAME_LEN 9 //8 caracteres

#define MAP_MAX_X 100
#define MAP_MAX_Y 100

#define NORTH 1
#define EAST 2
#define SOUTH 3
#define WEST 4

#define MAP_SIGNAL_KEY_COLLECTED (1<<0)
#define MAP_SIGNAL_PLAYER_DEFEATED (1<<1)

#define NEW_GAME 1
#define LOAD 2
#define CREDITS 3
#define EXIT 4
#define PLAYING 5

#endif
