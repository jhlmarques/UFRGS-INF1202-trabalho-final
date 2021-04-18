#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "menu.h"
#include "mobs.h"
#include "map.h"
#include "save_states.h"

pGame_map cur_map = NULL; //Mapa atual
pSave_state cur_save = NULL; //Gravação atual

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;
    int release = 1, state;

    InitWindow(screenWidth, screenHeight, "Trabalho Final - Jose Henrique Lima Marques e Matheus Almeida Silva");

    SetTargetFPS(60);

    while (!WindowShouldClose()){
        if(release == 1)
            state = menu();

        if (state == 1){
            release = 0;
            ClearBackground(RAYWHITE);
                DrawText("NEW GAME", 190, 200, 20, BLUE);
            EndDrawing();
            state = 5
            // NEW GAME
        }
        if (state == 2){
            release = 0;
            ClearBackground(RAYWHITE);
                DrawText("LOAD GAME", 190, 200, 20, BLUE);
            EndDrawing();
            state = 5
            // LOAD GAME
        }
        if (state == 3){    //CREDITS
            release = show_credits();
        }
        if (state == 4){    // EXIT
            break;
        }


    }
    CloseWindow();

    return 0;
}
