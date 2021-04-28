#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "defines.h"
#include "menu.h"
#include "mobs.h"
#include "map.h"
#include "save_states.h"
#include "player_movement.h"

pGame_map cur_map = NULL; //Mapa atual
pSave_state cur_save = NULL; //Gravação atual

int main(void) {
    const int screenWidth = SCREENWIDTH;
    const int screenHeight = SCREENHEIGHT;
    int game_state = STATE_MENU;
    int menu_oldstate;
    menu game_menu;
    set_basic_menu(&game_menu);

    InitWindow(screenWidth, screenHeight, WINDOW_NAME);

    SetTargetFPS(60);
    SetExitKey(0);

    while (!WindowShouldClose()){
        if(game_state == STATE_MENU){
            menu_oldstate = game_menu.state;
            menu_input(&game_menu);
            if(game_menu.selected){
                if(game_menu.selected == MENU_STEP_BACK){
                    menu_step_back(&game_menu, &game_state);
                }
                else{
                    menu_on_select(&game_menu, &game_state);
                }
            }
            else if(game_menu.taking_char_input){
                menu_char_input(&game_menu);
            }
            if(menu_oldstate != game_menu.state){
                set_menu_max_select(&game_menu);
            }
        }
        else if(game_state == STATE_STARTED_PLAYING){

        }
        else if(game_state == STATE_STOPPED_PLAYING){
            //Volta ao menu
        }
        else if(game_state == STATE_PLAYING){
            //Jogo
        }

        if(game_state == STATE_ENDED){
            break;
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            switch(game_state){
                case STATE_PLAYING:
                break;
                case STATE_MENU:
                draw_menu(&game_menu);
                break;
            }
        EndDrawing();


    }
    CloseWindow();




    return 0;
}
