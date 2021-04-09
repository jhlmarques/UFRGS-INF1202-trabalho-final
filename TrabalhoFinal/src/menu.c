#include "menu.h"
#include "raylib.h"


void wait(){
    int key;
    do{
        key = GetKeyPressed();
    }while(key != 48);
}

int menu(){
        int op, close = 1;

            BeginDrawing();
            ClearBackground(RAYWHITE);
                DrawText("Pressiona o numero:\n 1- NEW GAME\n 2- LOAD GAME\n 3- CREDITS\n 4- EXIT\n", 190, 200, 20, LIGHTGRAY);
            EndDrawing();

            op = GetKeyPressed();
            switch (op){
            case 49:
                BeginDrawing();
                ClearBackground(RAYWHITE);
                    DrawText("NEW GAME", 190, 200, 20, RED);
                    DrawText("Pressione o numero 0 para retornar ao menu principal\n", 190, 400, 20, LIGHTGRAY);
                EndDrawing();
                wait();
                break;
            case 50:
                BeginDrawing();
                ClearBackground(RAYWHITE);
                    DrawText("LISTA SAVES", 190, 200, 20, RED);
                    DrawText("Pressione o numero 0 para retornar ao menu principal\n", 190, 400, 20, LIGHTGRAY);
                EndDrawing();
                wait();
                break;
            case 51:
                BeginDrawing();
                ClearBackground(RAYWHITE);
                    DrawText("CREDITOS\n Jose Henrique Lima Marques\n Matheus Almeida Silva", 190, 200, 20, BLUE);
                    DrawText("Pressione o numero 0 para retornar ao menu principal\n", 190, 400, 20, LIGHTGRAY);
                EndDrawing();
                wait();
                break;
            case 52:
                close = 0;
                break;

            }
        return close;
}
