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

/*
VARIÁVEIS GLOBAIS
*/

//MAPA
pGame_map cur_map; //Mapa atual
pGame_map all_maps; //Vetor de mapas
int maps_loaded;//Quantidade de mapas carregados
//GRAVAÇÕES
pSave_state cur_save = NULL; //Gravação atual
save_state all_saves[MAX_SAVES]; //Todas Gravações
int saves_loaded; //Última quantidade de gravações lidas
//TIPOS DE CRIATURAS
pMob mob_types; //Vetor com todos tipos de criatura (DINAMICO)
int mob_type_amount; //Tamanho do vetor acima
//ESTADO DO JOGO
int game_state = STATE_MENU; //Estado do jogo
//JOGADOR
pMob player_mob; //Criatura controlada pelo jogador

int main(void) {
    const int screenWidth = SCREENWIDTH;
    const int screenHeight = SCREENHEIGHT;
    int menu_oldstate;
    menu game_menu;
    
    //Carregamento de structs essenciais
    SetBasicMenu(&game_menu);
    saves_loaded = LoadSaveFile(SAVEFILE_NAME, all_saves);
    LoadMobTypes(MOB_DEF_FILE);
    cur_map = (pGame_map) malloc(sizeof(game_map));

    //Definições gráficas
    InitWindow(screenWidth, screenHeight, WINDOW_NAME);

    SetTargetFPS(60);
    SetExitKey(0);

    //LOOP PRINCIPAL  
    while (!WindowShouldClose()){
        if(game_state == STATE_MENU){ //LÓGICA DO MENU
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
        else if(game_state == STATE_LOADING_MAP){//LÓGICA PRÉ-JOGO
            //Grava progresso
            WriteSaveToFile(SAVEFILE_NAME, cur_save, cur_save->save_id);
            if(!LoadCurMapFromMapList(MAPLIST_NAME, cur_save->cur_level)){
                cur_save->cur_level = 1;
                game_state = STATE_STOPPED_PLAYING;
            }
            else{
                player_mob = &cur_map->mobs[0]; //Primeira criatura sempre é o jogador
                game_state = STATE_PLAYING;
            }
        }
        else if(game_state == STATE_STOPPED_PLAYING){//LÓGICA PÓS-JOGO - PRÉ-MENU
            player_mob = NULL;
            MapFreeMap(cur_map);
            //Grava progresso
            WriteSaveToFile(SAVEFILE_NAME, cur_save, cur_save->save_id);
            //Volta ao menu
            SetBasicMenu(&game_menu);
            game_state = STATE_MENU;
        }
        else if(game_state == STATE_PLAYING){//LÓGICA DO JOGO
            if(CheckPaused()){
                game_state = STATE_MENU;
                game_menu.state = MENU_PAUSED;
                SetMenuMaxSelect(&game_menu);
            }
            else{
                GameLoop();
            }
        }

        if(game_state == STATE_ENDED){//QUEBRA DO LOOP
            break;
        }

        //FUNÇÕES GRÁFICAS
        BeginDrawing();
            ClearBackground(RAYWHITE);
            switch(game_state){
                case STATE_PLAYING:
                system("cls"); //Placeholder
                printf("MAPA: %d VIDAS: %d PONTOS: %d INIMIGOS: %d\n", cur_save->cur_level, cur_save->lives, \
                                                                        cur_save->points, cur_map->enemies_left);
                PrintMap_ASCII(cur_map);
                break;
                case STATE_MENU:
                DrawMenu(&game_menu);
                break;
            }
        EndDrawing();


    }

    //LIMPEZA PRÉ-ENCERRAMENTO DO JOGO
    CloseWindow();

    player_mob = NULL;
    if(cur_map != NULL){
        MapFreeMap(cur_map);
    }
    free(mob_types);



    return 0;
}
