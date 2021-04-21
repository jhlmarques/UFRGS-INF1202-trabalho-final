#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "defines.h"

typedef struct menu{
    int selection;
    int selected;
    int max_selection;
    int state;
    int taking_char_input;
    char input_buffer[PLAYER_NAME_LEN];
    int buffer_pos;
}menu, *pMenu;

void set_basic_menu(pMenu game_menu);

void menu_input(pMenu game_menu);

void menu_step_back(pMenu game_menu, int* game_state);

void menu_on_select(pMenu game_menu, int* game_state);

void set_menu_max_select(pMenu game_menu);

void menu_char_input(pMenu game_menu);

void draw_menu(pMenu game_menu);

#endif // MENU_H_INCLUDED
