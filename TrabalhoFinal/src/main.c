#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "menu.h"
#include "mobs.h"
#include "map.h"
#include "save_states.h"
#include "player_movement.h"

pGame_map cur_map = NULL; //Mapa atual
pSave_state cur_save = NULL; //Gravação atual

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;
    mob player = {3, 0, 0, NULL, { (float)screenWidth/2, (float)screenHeight/2 }, NEUTRAL, PLAYER_ID, PLAYER_ID};
    pMob pPlayer = &player;
    int release = 1, state;

    InitWindow(screenWidth, screenHeight, "Trabalho Final - Jose Henrique Lima Marques e Matheus Almeida Silva");

    SetTargetFPS(60);

    while (!WindowShouldClose()){
        if(release == 1)
            state = menu();

        if (state == NEW_GAME){
            release = 0;
            ClearBackground(RAYWHITE);
                DrawText("NEW GAME", 190, 200, 20, BLUE);
            EndDrawing();
            state = PLAYING;
            // NEW GAME
        }
        if (state == LOAD){
            release = 0;
            ClearBackground(RAYWHITE);
                DrawText("LOAD GAME", 190, 200, 20, BLUE);
            EndDrawing();
            state = PLAYING;
            // LOAD GAME
        }
        if (state == CREDITS){    //CREDITS
            release = show_credits();
        }
        if (state == EXIT){    // EXIT
            break;
        }

        if (state == PLAYING){
            player_movement(pPlayer);
        }


    }
    CloseWindow();




    return 0;
}
