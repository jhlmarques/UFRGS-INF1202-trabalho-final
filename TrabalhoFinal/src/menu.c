#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "raylib.h"
#include "defines.h"
#include "globals.h"
#include "save_states.h"


void set_basic_menu(pMenu game_menu){
    game_menu->selection = 0;
    game_menu->selected = 0;
    game_menu->state = MAIN_MENU;
    game_menu->max_selection = MAIN_MENU_MAX_SELECT;
    game_menu->buffer_pos = 0;
    game_menu->taking_char_input = 0;
}

void draw_menu(pMenu game_menu){
    switch(game_menu->state){

        case MAIN_MENU:{
            DrawText("NEW GAME\nLOAD GAME\nCREDITS\nEXIT\n", 190, 200, 20, BLACK); //Fun��o de Escrita da raylib
            DrawCircle(170, 180 + (game_menu->selection * 30), 5.0, BLACK);
            break;
        }
        case MENU_NEWGAME:{
            DrawText(TextFormat("Digite o seu nome (%d/%d)", game_menu->buffer_pos, PLAYER_NAME_LEN - 1), 190, 200, 20, BLACK);
            DrawText(game_menu->input_buffer, 190, 220, 20, BLACK);
            break;
        }
        case MENU_DELETE_SAVE:{
            DrawText("Limite de gravações atingido!\nEscolha uma gravação para sobrescrever", 190, 100, 20, RED);
        }
        case MENU_LOADGAME:{
            if(saves_loaded < 0){
                DrawText("Erro ao carregar o arquivo de gravações", 190, 200, 20, BLACK);
            }
            else{
                int i, y_pos = 200;
                pSave_state save;
                DrawText("Escolha uma gravação:", 190, 160, 20, BLACK);
                for(i = 0; i < saves_loaded; i++){
                    save = all_saves + i;
                    DrawText(TextFormat("%d - %s: Fase: %d Vidas: %d Pontos: %d", \
                    save->save_id, save->player_name, save->cur_level, save->lives, save->points),\
                     190, y_pos, 20, ORANGE);
                    y_pos += 30;
                }
                if(saves_loaded){
                    DrawCircle(170, 180 + (game_menu->selection * 30), 5.0, BLACK);
                }
            }

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
            game_menu->selection--;
        }
        else if(IsKeyPressed(KEY_DOWN)){
            game_menu->selection++;
        }
        game_menu->selection = MAX(MIN(game_menu->selection, game_menu->max_selection), 1);
    }
}

void menu_step_back(pMenu game_menu, int* game_state){
    switch(game_menu->state){
        case MAIN_MENU:
        break;
        case MENU_NEWGAME:
        game_menu->state = MAIN_MENU;
        game_menu->taking_char_input = 0;
        break;
        case MENU_CREDITS:
        case MENU_LOADGAME:
        case MENU_DELETE_SAVE:
        game_menu->state = MAIN_MENU;
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
                if(saves_loaded < MAX_SAVES){
                    game_menu->state = MENU_NEWGAME;
                    game_menu->taking_char_input = 1;
                    memset(game_menu->input_buffer, '\0', PLAYER_NAME_LEN);
                    game_menu->buffer_pos = 0;
                }
                else{
                    game_menu->state = MENU_DELETE_SAVE;
                }
                break;
                case 2:
                game_menu->state = MENU_LOADGAME;
                saves_loaded = load_save_file(SAVEFILE_NAME, all_saves);
                break;
                case 3:
                game_menu->state = MENU_CREDITS;
                break;
                case MAIN_MENU_MAX_SELECT: //Sair
                *game_state = STATE_ENDED;
                break;
            }
            break;
        case MENU_NEWGAME:
            if(game_menu->buffer_pos > 0 && saves_loaded < MAX_SAVES){
                new_save_state(all_saves + saves_loaded, game_menu->input_buffer);
                write_save_to_file(SAVEFILE_NAME, all_saves + saves_loaded, saves_loaded + 1);
                saves_loaded++;
                menu_step_back(game_menu, game_state); //Por enquanto só volta ao menu
            }
            break;
        case MENU_LOADGAME:
            menu_step_back(game_menu, game_state); //Por enquanto só volta ao menu
            break;
        case MENU_DELETE_SAVE:
            delete_save(SAVEFILE_NAME, game_menu->selected);
            saves_loaded--;
            menu_step_back(game_menu, game_state);
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
        game_menu->max_selection = 1;
        break;
        case MENU_LOADGAME:
        case MENU_DELETE_SAVE:
        game_menu->max_selection = saves_loaded;
        break;
        case MENU_CREDITS:
        game_menu->max_selection = 0;
        break;
    }
}

void menu_char_input(pMenu game_menu){
    char key;
    if(IsKeyPressed(KEY_BACKSPACE)){
        game_menu->buffer_pos = MAX(0, game_menu->buffer_pos - 1);
        game_menu->input_buffer[game_menu->buffer_pos] = '\0';
    }
    else if(game_menu->buffer_pos < PLAYER_NAME_LEN - 1){
        if((key = GetCharPressed())){
            game_menu->input_buffer[game_menu->buffer_pos] = key;
            game_menu->buffer_pos++;
        }
    }
}
