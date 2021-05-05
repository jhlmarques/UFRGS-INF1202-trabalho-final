#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "defines.h"
#include "globals.h"
#include "menu.h"
#include "mobs.h"
#include "map.h"
#include "save_states.h"
#include "game.h"


pGame_map cur_map; //Mapa atual
pSave_state cur_save = NULL; //Gravação atual
save_state all_saves[MAX_SAVES]; //Todas Gravações
int saves_loaded; //Última quantidade de gravações lidas
pMob mob_types; //Vetor com todos tipos de criatura (DINAMICO)
int mob_type_amount; //Tamanho do vetor acima
int game_state = STATE_MENU; //Estado do jogo

int main(void) {
    const int screenWidth = SCREENWIDTH;
    const int screenHeight = SCREENHEIGHT;
    int menu_oldstate;
    menu game_menu;
    pMob player_mob;

    SetBasicMenu(&game_menu);
    saves_loaded = LoadSaveFile(SAVEFILE_NAME, all_saves);
    LoadMobTypes(MOB_DEF_FILE);

    InitWindow(screenWidth, screenHeight, WINDOW_NAME);

    SetTargetFPS(60);
    SetExitKey(0);

    while (!WindowShouldClose()){
        if(game_state == STATE_MENU){
            menu_oldstate = game_menu.state;
            MenuInput(&game_menu);
            if(game_menu.selected){
                if(game_menu.selected == MENU_STEP_BACK){
                    MenuStepBack(&game_menu);
                }
                else{
                    MenuOnSelect(&game_menu);
                }
            }
            else if(game_menu.taking_char_input){
                MenuCharInput(&game_menu);
            }
            if(menu_oldstate != game_menu.state){
                SetMenuMaxSelect(&game_menu);
            }
        }
        else if(game_state == STATE_STARTED_PLAYING){
            //Carrega o que é necessário para o jogo
            cur_map = (pGame_map) malloc(sizeof(game_map));
            LoadMap("maps/testmap.txt", cur_map);
            player_mob = &cur_map->mobs[0]; //Primeira criatura sempre é o jogador
            game_state = STATE_PLAYING;
        }
        else if(game_state == STATE_STOPPED_PLAYING){
            player_mob = NULL;
            MapFreeMap(cur_map);
            cur_map = NULL;
            //Volta ao menu
            SetBasicMenu(&game_menu);
            game_state = STATE_MENU;
        }
        else if(game_state == STATE_PLAYING){
            //Jogo
            if(CheckPaused()){
                game_state = STATE_MENU;
                game_menu.state = MENU_PAUSED;
                SetMenuMaxSelect(&game_menu);
            }
            else{
                GameLoop(player_mob);
            }
        }

        if(game_state == STATE_ENDED){
            break;
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            switch(game_state){
                case STATE_PLAYING:
                system("cls"); //Placeholder
                PrintMap_ASCII(cur_map);
                break;
                case STATE_MENU:
                DrawMenu(&game_menu);
                break;
            }
        EndDrawing();


    }
    CloseWindow();

    player_mob = NULL;
    if(cur_map != NULL){
        MapFreeMap(cur_map);
    }
    free(mob_types);



    return 0;
}
