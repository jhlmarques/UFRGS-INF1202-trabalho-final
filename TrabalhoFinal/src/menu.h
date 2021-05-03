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

void SetBasicMenu(pMenu game_menu);

void MenuInput(pMenu game_menu);

void MenuStepBack(pMenu game_menu, int* game_state);

void MenuOnSelect(pMenu game_menu, int* game_state);

void SetMenuMaxSelect(pMenu game_menu);

void MenuCharInput(pMenu game_menu);

void DrawMenu(pMenu game_menu);

#endif // MENU_H_INCLUDED
