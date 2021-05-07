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
#include "items.h"
#include "mob_movement.h"
#include "turfs.h"
#include "point.h"

/*Funções gráficas a serem implementadas com a Raylib   , podendo constar ou não no jogo final entregue. Uso não avaliativo*/

void DrawPlayer(Vector2 position){
    Texture2D player = LoadTexture("textures/player_2.png");
    Texture2D background = LoadTexture("textures/floor_1.png");
    int frameWidth = player.width;
    int frameHeight = player.height;
    Rectangle rec = {0, 0, (float)frameWidth, (float)frameHeight};
    Rectangle back = {0, 0, background.width, background.height};

    BeginDrawing();

        DrawTextureRec(background, back, position, RAYWHITE);
        DrawTextureRec(player, rec, position, RAYWHITE);

    EndDrawing();

}

void DrawFloor(Vector2 position){
    Texture2D background = LoadTexture("textures/floor_1.png");
    Rectangle back = {0, 0, background.width, background.height};

    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextureRec(background, back, position, RAYWHITE);
    EndDrawing();

}

void DrawWall(Vector2 position){
    if(position.x == 0 || position.x == 765){
        Texture2D wall = LoadTexture("textures/wall_up.png");
        int frameWidth = wall.width;
        int frameHeight = wall.height;
        Rectangle rec = {0, 0, (float)frameWidth, (float)frameHeight};

        BeginDrawing();
            DrawTextureRec(wall, rec, position, RAYWHITE);
        EndDrawing();

    } else if (position.y == 0 ){
        Texture2D wall = LoadTexture("textures/wall_side.png");
        int frameWidth = wall.width;
        int frameHeight = wall.height;
        Rectangle rec = {0, 0, (float)frameWidth, (float)frameHeight};

        BeginDrawing();
            DrawTextureRec(wall, rec, position, RAYWHITE);
        EndDrawing();

    } else if (position.y == 450){
        Texture2D wall = LoadTexture("textures/wall_bottom.png");
        int frameWidth = wall.width;
        int frameHeight = wall.height;
        Rectangle rec = {0, 0, (float)frameWidth, (float)frameHeight};

        BeginDrawing();
            DrawTextureRec(wall, rec, position, RAYWHITE);
        EndDrawing();

    }

}

void DrawEnemy(Vector2 position){
    Texture2D enemy = LoadTexture("textures/enemy_2.png");
    Texture2D background = LoadTexture("textures/floor_1.png");
    int frameWidth = enemy.width;
    int frameHeight = enemy.height;
    Rectangle rec = {0, 0, (float)frameWidth, (float)frameHeight};
    Rectangle back = {0, 0, background.width, background.height};

    BeginDrawing();

        DrawTextureRec(background, back, position, RAYWHITE);
        DrawTextureRec(enemy, rec, position, RAYWHITE);

    EndDrawing();
}

void DrawHeart(Vector2 position){
    Texture2D heart = LoadTexture("textures/heart_1.png");
    Texture2D background = LoadTexture("textures/floor_1.png");
    int frameWidth = heart.width;
    int frameHeight = heart.height;
    Rectangle rec = {0, 0, (float)frameWidth, (float)frameHeight};
    Rectangle back = {0, 0, background.width, background.height};

    BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTextureRec(background, back, position, RAYWHITE);
        DrawTextureRec(heart, rec, position, RAYWHITE);

    EndDrawing();
}

void DrawBall(Vector2 position) {
    Texture2D ball = LoadTexture("textures/ball.png");
    Texture2D background = LoadTexture("textures/floor_1.png");
    int frameWidth = ball.width;
    int frameHeight = ball.height;
    Rectangle rec = {0, 0, (float)frameWidth, (float)frameHeight};
    Rectangle back = {0, 0, background.width, background.height};

    BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTextureRec(background, back, position, RAYWHITE);
        DrawTextureRec(ball, rec, position, RAYWHITE);

    EndDrawing();

}

void DrawRock(Vector2 position){
    Texture2D rock = LoadTexture("textures/rock_1.png");
    Texture2D background = LoadTexture("textures/floor_1.png");
    int frameWidth = rock.width;
    int frameHeight = rock.height;
    Rectangle rec = {0, 0, (float)frameWidth, (float)frameHeight};
    Rectangle back = {0, 0, background.width, background.height};

    BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTextureRec(background, back, position, RAYWHITE);
        DrawTextureRec(rock, rec, position, RAYWHITE);

    EndDrawing();

}

void DrawBlock(Vector2 position){
    Texture2D block = LoadTexture("textures/block.png");
    Texture2D background = LoadTexture("textures/floor_1.png");
    int frameWidth = block.width;
    int frameHeight = block.height;
    Rectangle rec = {0, 0, (float)frameWidth, (float)frameHeight};
    Rectangle back = {0, 0, background.width, background.height};

    BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTextureRec(background, back, position, RAYWHITE);
        DrawTextureRec(block, rec, position, RAYWHITE);

    EndDrawing();

}

void DrawDoor(Vector2 position, int signal){
    if (signal == MAP_SIGNAL_KEY_COLLECTED){
        Texture2D door = LoadTexture("textures/door_closed.png");
        Texture2D background = LoadTexture("textures/wall_up.png");
        int frameWidth = door.width;
        int frameHeight = door.height;
        Rectangle rec = {0, 0, (float)frameWidth, (float)frameHeight};
        Rectangle back = {0, 0, background.width, background.height};

        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawTextureRec(background, back, position, RAYWHITE);
            DrawTextureRec(door, rec, position, RAYWHITE);

        EndDrawing();
    } else {
        Texture2D door = LoadTexture("textures/door_open.png");
        Texture2D background = LoadTexture("textures/wall_up.png");
        int frameWidth = door.width;
        int frameHeight = door.height;
        Rectangle rec = {0, 0, (float)frameWidth, (float)frameHeight};
        Rectangle back = {0, 0, background.width, background.height};

        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawTextureRec(background, back, position, RAYWHITE);
            DrawTextureRec(door, rec, position, RAYWHITE);

        EndDrawing();

    }

}

void DrawMenuBackground(Vector2 position){
    Texture2D background = LoadTexture("textures/menu_background.png");
    Rectangle back = {0, 0, background.width, background.height};

    BeginDrawing();
        DrawTextureRec(background, back, position, RAYWHITE);
        DrawText("Castle Adventure", 200, 100, 50, RED);
    EndDrawing();
}

void DrawMap(pGame_map map) {
    int i, j;
    pTurf T;
    for(i = 0; i < map->bounds_y; i++){
        for(j = 0; j < map->bounds_x; j++){
            T = &pMAP_ACESS_TURF(map, j, i);
            if(pTURF_IS_SOLID(T)){

            }
            else if(pTURF_HAS_MOB(T) || pTURF_HAS_ITEM(T)){
                if(!pTURF_HAS_ITEM(T)){

                    if(T->cur_mob == PLAYER_ID){

                    }
                    else if (T->cur_mob != PLAYER_ID){

                    }
                }
                else if(!pTURF_HAS_MOB(T)){

                }
                else{

                }

            }
            else{

            }


        }

    }

}




