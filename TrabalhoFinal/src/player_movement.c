#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "mobs.h"
#include "map.h"
#include "point.h"
#include "save_states.h"

void PlayerMovement(pMob pPlayer){
    if (IsKeyDown(KEY_RIGHT)){
        pPlayer->dir = EAST;
        if(MoveCheckInteractions(pPlayer)) pPlayer->pos.x += 2.0f;
    }

    if (IsKeyDown(KEY_LEFT)){
        pPlayer->dir = WEST;
        if(MoveCheckInteractions(pPlayer)) pPlayer->pos.x -= 2.0f;
    }
    if (IsKeyDown(KEY_UP)){
        pPlayer->dir = NORTH;
        if(MoveCheckInteractions(pPlayer)) pPlayer->pos.y -= 2.0f;
    }
    if (IsKeyDown(KEY_DOWN)){
        pPlayer->dir = SOUTH;
        if(MoveCheckInteractions(pPlayer)) pPlayer->pos.y += 2.0f;
    }

    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircleV(pPlayer->pos, 10, BLUE);
    EndDrawing();

}
