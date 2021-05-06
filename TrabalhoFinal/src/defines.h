#ifndef _defines_h_
#define _defines_h_

#include <stddef.h>

#define SAVEFILE_NAME "saves.save"
#define MAPLIST_NAME "maps/maplist.txt"
#define MOB_DEF_FILE "mob_definitions.txt"
#define MAX_SAVES 4

#define SCREENHEIGHT 450
#define SCREENWIDTH 800

#define WINDOW_NAME "Trabalho Final - Jose Henrique Lima Marques e Matheus Almeida Silva"

#define STATE_MENU 1
#define STATE_PLAYING 2
#define STATE_LOADING_MAP 3
#define STATE_STOPPED_PLAYING 4
#define STATE_ENDED -1

#define MENU_STEP_BACK -1

#define MAIN_MENU_MAX_SELECT 4

#define MAIN_MENU 1
#define MENU_CREDITS 2
#define MENU_NEWGAME 3
#define MENU_LOADGAME 4
#define MENU_DELETE_SAVE 5
#define MENU_PAUSED 6

#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a < b) ? a : b)

//Fac��es
#define NEUTRAL 0
#define FRIENDLY 1
#define HOSTILE 2

#define PLAYER_ID 0
#define NO_ID -1

#define POINT_REWARD_ENEMY_DEFEATED 100

#define PLAYER_NAME_LEN 9 //8 caracteres

#define MAP_MAX_X 100
#define MAP_MAX_Y 100

#define MAX_MOVEMENT_COMMANDS 10

#define NORTH 1
#define EAST 2
#define SOUTH 3
#define WEST 4

#define ITEM_KEY 1
#define ITEM_WATER 2
#define ITEM_EXIT 3



#endif
