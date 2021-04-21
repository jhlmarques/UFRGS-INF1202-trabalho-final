#include "menu.h"
#include "raylib.h"
#include <stdio.h>
#include "defines.h"

void set_basic_menu(pMenu game_menu){
    game_menu->selection = 0;
    game_menu->selected = 0;
    game_menu->state = MAIN_MENU;
    game_menu->max_selection = MAIN_MENU_MAX_SELECT;
    game_menu->buffer_pos = 0;
    game_menu->taking_char_input = 0;
}

void draw_menu(pMenu game_menu){
    DrawText(TextFormat("Selection: %d\nSelected: %d\n", game_menu->selection, game_menu->selected), 190, 100, 20, LIGHTGRAY);
    switch(game_menu->state){
        
        case MAIN_MENU:{
            DrawText("Pressiona o numero:\n 1- NEW GAME\n 2- LOAD GAME\n 3- CREDITS\n 4- EXIT\n", 190, 200, 20, LIGHTGRAY); //Fun��o de Escrita da raylib
            break;
        }
        case MENU_NEWGAME:{
            DrawText("Novo jogo indisponível no momento", 190, 200, 20, LIGHTGRAY);
            break;
        }
        case MENU_LOADGAME:{
            DrawText("Carregar jogo indisponível no momento", 190, 200, 20, LIGHTGRAY);
            break;
        }
        case MENU_CREDITS:{
            DrawText("CREDITOS\n Jose Henrique Lima Marques\n Matheus Almeida Silva", 190, 200, 20, BLUE);
            break;
        }
        

    }

}

void menu_input(pMenu game_menu){
    game_menu->selected = 0;
    if(IsKeyPressed(KEY_ENTER)){
        game_menu->selected = game_menu->selection;
    }
    else if(IsKeyPressed(KEY_ESCAPE)){
        game_menu->selected = MENU_STEP_BACK;
    }
    else if(game_menu->max_selection > 1){
        if(IsKeyPressed(KEY_UP)){
            game_menu->selection++;
        }
        else if(IsKeyPressed(KEY_DOWN)){
            game_menu->selection--;
        }
        if(game_menu->selection < 1){
            game_menu->selection = 1;
        }
        game_menu->selection = MIN(game_menu->selection, game_menu->max_selection);
    }
}

void menu_step_back(pMenu game_menu, int* game_state){
    switch(game_menu->state){
        case MAIN_MENU:
        break;
        case MENU_CREDITS:
        case MENU_NEWGAME:
        case MENU_LOADGAME:
        game_menu->state = MAIN_MENU;
        break;
        case MENU_INPUT_NEWGAME:
        game_menu->state = MENU_NEWGAME;
        break;
        case MENU_PAUSED:
        game_menu->state = STATE_PLAYING;
        break;
    }
}

void menu_on_select(pMenu game_menu, int* game_state){
    switch(game_menu->state){
        case MAIN_MENU:
            switch(game_menu->selected){
                case 1:
                game_menu->state = MENU_NEWGAME;
                break;
                case 2:
                game_menu->state = MENU_LOADGAME;
                break;
                case 3:
                game_menu->state = MENU_CREDITS;
                break;
                case MAIN_MENU_MAX_SELECT: //Sair
                *game_state = STATE_ENDED;
                break;
            }
            break;
        case MENU_INPUT_NEWGAME:


            break;
        case MENU_PAUSED:
            switch(game_menu->selected){
                case 1:
                *game_state = STATE_PLAYING;
                break;
                case 2:
                *game_state = STATE_STOPPED_PLAYING;
            }
            break;
    }
}

void set_menu_max_select(pMenu game_menu){
    switch(game_menu->state){
        case MAIN_MENU:
        game_menu->max_selection = MAIN_MENU_MAX_SELECT;
        break;
        case MENU_NEWGAME:
        case MENU_LOADGAME:
        //Numero de gravações + sair
        break;
        case MENU_INPUT_NEWGAME:
        game_menu->max_selection = 1;
        break;
        case MENU_CREDITS:
        game_menu->max_selection = 0;
        break;
    }
}

void menu_char_input(pMenu game_menu){
    if(IsKeyPressed(KEY_BACKSPACE)){
        game_menu->input_buffer[game_menu->buffer_pos] = '\0';
        game_menu->buffer_pos = MIN(0, game_menu->buffer_pos - 1);
    }
    else if(game_menu->buffer_pos < PLAYER_NAME_LEN){
        game_menu->input_buffer[game_menu->buffer_pos] = GetCharPressed();
        game_menu->buffer_pos = MIN(PLAYER_NAME_LEN, game_menu->buffer_pos + 1);
    }
}
