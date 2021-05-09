#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "defines.h"

typedef struct menu{
    int selection; //Posição do seletor atual
    int selected; //Última posição confirmada do seletor
    int max_selection; //Posição máximo do seletor
    int state; //Estado atual do menu
    int taking_char_input; //Recebendo input de caracteres?
    char input_buffer[PLAYER_NAME_LEN]; //Buffer de input de caracteres
    int buffer_pos; //Posição atual de escrita no buffer
}menu, *pMenu;

//Definições básicas de um menu
void SetBasicMenu(pMenu game_menu);

//Lida com o input do menu
void MenuInput(pMenu game_menu);

//Lida com o comando de "voltar para o menu anterior"
void MenuStepBack(pMenu game_menu);

//Lida com a confirmação de seleção do jogador
void MenuOnSelect(pMenu game_menu);

//Define o limite de seleção
void SetMenuMaxSelect(pMenu game_menu);

//Lida com o input de caracteres
void MenuCharInput(pMenu game_menu);

#endif // MENU_H_INCLUDED
