#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "mobs.h"
#include "map.h"
#include "save_states.h"

void player_movement(pMob pPlayer){
    if (IsKeyDown(KEY_RIGHT)) pPlayer->pos.x += 5.0f;
    if (IsKeyDown(KEY_LEFT)) pPlayer->pos.x -= 5.0f;
    if (IsKeyDown(KEY_UP)) pPlayer->pos.y -= 5.0f;
    if (IsKeyDown(KEY_DOWN)) pPlayer->pos.y += 5.0f;

    BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("NEW GAME", 10, 10, 20, DARKGRAY);

        DrawCircleV(pPlayer->pos, 10, BLUE);

    EndDrawing();

}
