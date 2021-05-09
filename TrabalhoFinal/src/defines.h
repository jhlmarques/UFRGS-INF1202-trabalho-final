#ifndef _defines_h_
#define _defines_h_

//ARQUIVOS
#define SAVEFILE_NAME "saves.save"
#define MAPLIST_NAME "maps/maplist.txt"
#define MOB_DEF_FILE "mob_definitions.txt"
#define TEXTURES_FILE "textures/textures.txt"
#define BASE_MOB_TEXTURE_FILE "textures/mob.png"
#define BASE_ITEM_TEXTURE_FILE "textures/item.png"
#define BASE_TURF_TEXTURE_FILE "textures/turf.png"

//GRAVAÇÕES
#define MAX_SAVES 4

//MAPA
#define MAP_MAX_X 100
#define MAP_MAX_Y 100

//ESTADOS DO JOGO
#define STATE_MENU 1
#define STATE_PLAYING 2
#define STATE_LOADING_MAP 3
#define STATE_STOPPED_PLAYING 4
#define STATE_ENDED -1

//MENU
#define MENU_STEP_BACK -1

#define MAIN_MENU_MAX_SELECT 4

#define MAIN_MENU 1
#define MENU_CREDITS 2
#define MENU_NEWGAME 3
#define MENU_LOADGAME 4
#define MENU_DELETE_SAVE 5
#define MENU_PAUSED 6

//IDS
#define PLAYER_ID 0
#define NO_ID -1

//CRIATURAS
#define NEUTRAL 0
#define FRIENDLY 1
#define HOSTILE 2
#define MAX_MOVEMENT_COMMANDS 10
#define POINT_REWARD_ENEMY_DEFEATED 1
#define POINTS_EXTRA_LIFE 10

//ITENS

#define ITEM_POWER 1
#define ITEM_WATER 2
#define ITEM_KEY 3
#define ITEM_EXIT 4

//RAYLIB E GRAFICOS
#define WINDOW_NAME "Trabalho Final - Jose Henrique Lima Marques e Matheus Almeida Silva"
#define SCREENHEIGHT 450
#define SCREENWIDTH 800
#define TEXTURE_PLAYER 4
#define TEXTURE_SIZE 32
#define MAP_DRAW_Y_OFFSET 32
#define INFO_X_DRAWPOS 0
#define INFO_Y_DRAWPOS 16

//MISC
#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a < b) ? a : b)
#define PLAYER_NAME_LEN 9 //8 caracteres
#define NORTH 1
#define EAST 2
#define SOUTH 3
#define WEST 4

#endif
