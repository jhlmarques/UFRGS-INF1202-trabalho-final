#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "defines.h"
#include "globals.h"
#include "menu.h"
#include "mobs.h"
#include "map.h"
#include "save_states.h"
#include "player_movement.h"

game_map cur_map; //Mapa atual
pSave_state cur_save = NULL; //Gravação atual
save_state all_saves[MAX_SAVES]; //Todas Gravações
int saves_loaded; //Última quantidade de gravações lidas
pMob mob_types; //Vetor com todos tipos de criatura (DINAMICO)
int mob_type_amount; //Tamanho do vetor acima

int main(void) {
    const int screenWidth = SCREENWIDTH;
    const int screenHeight = SCREENHEIGHT;
    int game_state = STATE_MENU;
    int menu_oldstate;
    menu game_menu;

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
                    MenuStepBack(&game_menu, &game_state);
                }
                else{
                    MenuOnSelect(&game_menu, &game_state);
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
            puts("CARREGANDO O JOGO...");
            LoadMap("maps/testmap.txt");
            game_state = STATE_PLAYING;
        }
        else if(game_state == STATE_STOPPED_PLAYING){
            //Volta ao menu
        }
        else if(game_state == STATE_PLAYING){
            //Jogo
        }

        if(game_state == STATE_ENDED){
            free(mob_types);
            break;
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            switch(game_state){
                case STATE_PLAYING:
                system("cls"); //Placeholder
                PrintMap_ASCII(&cur_map);
                break;
                case STATE_MENU:
                DrawMenu(&game_menu);
                break;
            }
        EndDrawing();


    }
    CloseWindow();




    return 0;
}
