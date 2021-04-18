#include "menu.h"
#include "raylib.h"
#include <stdio.h>

int menu(){
        int state;
        BeginDrawing();
        ClearBackground(RAYWHITE);
            DrawText("Pressiona o numero:\n 1- NEW GAME\n 2- LOAD GAME\n 3- CREDITS\n 4- EXIT\n", 190, 200, 20, LIGHTGRAY); //Função de Escrita da raylib
        EndDrawing();

         if(IsKeyPressed(KEY_ONE)){
            state = 1;
         }
        if(IsKeyPressed(KEY_TWO)){
            state = 2;
        }
        if(IsKeyPressed(KEY_THREE)){
            state = 3;
        }
        if(IsKeyPressed(KEY_FOUR)){
            state = 4;
        }
        return state;
}

int show_credits() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
        DrawText("CREDITOS\n Jose Henrique Lima Marques\n Matheus Almeida Silva", 190, 200, 20, BLUE);
        DrawText("Pressione o numero ESPACO para retornar ao menu principal\n", 190, 400, 20, LIGHTGRAY);
    EndDrawing();
    if(IsKeyPressed(KEY_SPACE))
        return 1;
    else
        return 0;
}
