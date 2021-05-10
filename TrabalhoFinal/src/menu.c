#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "raylib.h"
#include "defines.h"
#include "globals.h"
#include "save_states.h"


void SetBasicMenu(pMenu game_menu){
    game_menu->selection = 0;
    game_menu->selected = 0;
    game_menu->state = MAIN_MENU;
    game_menu->max_selection = MAIN_MENU_MAX_SELECT;
    game_menu->buffer_pos = 0;
    game_menu->taking_char_input = 0;
}

void MenuInput(pMenu game_menu){
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

void MenuStepBack(pMenu game_menu){
    switch(game_menu->state){
        case MAIN_MENU:
        break;
        case MENU_NEWGAME:
        game_menu->taking_char_input = 0;
        case MENU_CREDITS:
        case MENU_LOADGAME:
        case MENU_DELETE_SAVE:
        game_menu->state = MAIN_MENU;
        break;
        case MENU_PAUSED:
        game_state = STATE_PLAYING;
        break;
    }
}

void MenuOnSelect(pMenu game_menu){
    switch(game_menu->state){
        case MAIN_MENU:
            switch(game_menu->selected){
                case 1:
                if(saves_loaded < 0){
                    break;
                }
                else if(saves_loaded < MAX_SAVES){
                    game_menu->state = MENU_NEWGAME;
                    game_menu->taking_char_input = 1;
                    memset(game_menu->input_buffer, '\0', PLAYER_NAME_LEN);
                    game_menu->buffer_pos = 0;
                }
                else{
                    game_menu->state = MENU_DELETE_SAVE;
                    saves_loaded = LoadSaveFile(SAVEFILE_NAME, all_saves);
                }
                break;
                case 2:
                game_menu->state = MENU_LOADGAME;
                saves_loaded = LoadSaveFile(SAVEFILE_NAME, all_saves);
                break;
                case 3:
                game_menu->state = MENU_CREDITS;
                break;
                case MAIN_MENU_MAX_SELECT: //Sair
                game_state = STATE_ENDED;
                break;
            }
            break;
        case MENU_NEWGAME:
            if(game_menu->buffer_pos > 0 && saves_loaded < MAX_SAVES){
                pSave_state new = all_saves + saves_loaded;
                NewSaveState(new, game_menu->input_buffer, saves_loaded);
                WriteSaveToFile(SAVEFILE_NAME, new, saves_loaded);
                cur_save = &all_saves[saves_loaded];
                saves_loaded++;
                game_state = STATE_LOADING_MAP;
            }
            break;
        case MENU_LOADGAME:
            if(game_menu->selected == game_menu->max_selection){
                game_menu->state = MENU_DELETE_SAVE;
            }
            else{
                cur_save = &all_saves[game_menu->selected - 1];
                game_state = STATE_LOADING_MAP;
            }
            break;
        case MENU_DELETE_SAVE:
            if(saves_loaded){
                DeleteSaveFromFile(SAVEFILE_NAME, game_menu->selected);
                saves_loaded--;
                MenuStepBack(game_menu);
            }
            break;
        case MENU_PAUSED:
            switch(game_menu->selected){
                case 1:
                game_state = STATE_PLAYING;
                break;
                case 2:
                game_state = STATE_STOPPED_PLAYING;
                break;
            }
            break;
    }
}

void SetMenuMaxSelect(pMenu game_menu){
    game_menu->selection = 1;
    switch(game_menu->state){
        case MAIN_MENU:
        game_menu->max_selection = MAIN_MENU_MAX_SELECT;
        break;
        case MENU_NEWGAME:
        game_menu->max_selection = 1;
        break;
        case MENU_LOADGAME:
        game_menu->max_selection = saves_loaded + 1;
        break;
        case MENU_DELETE_SAVE:
        game_menu->max_selection = saves_loaded;
        break;
        case MENU_CREDITS:
        game_menu->max_selection = 0;
        case MENU_PAUSED:
        game_menu->max_selection = 2;
        break;
    }
}

void MenuCharInput(pMenu game_menu){
    if(IsKeyPressed(KEY_BACKSPACE)){
        game_menu->buffer_pos = MAX(0, game_menu->buffer_pos - 1);
        game_menu->input_buffer[game_menu->buffer_pos] = '\0';
    }
    else if(game_menu->buffer_pos < PLAYER_NAME_LEN - 1){
        char key;
        if((key = GetCharPressed())){
            game_menu->input_buffer[game_menu->buffer_pos] = key;
            game_menu->buffer_pos++;
        }
    }
}
