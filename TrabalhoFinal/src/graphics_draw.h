#ifndef _graphics_draw_h_
#define _graphics_draw_h_

#include "raylib.h"
#include "defines.h"
#include "mobs.h"
#include "items.h"
#include "turfs.h"
#include "map.h"

void DrawPlayer(Vector2 position);
void DrawFloor(Vector2 position);
void DrawWall(Vector2 position);
void DrawEnemy(Vector2 position);
void DrawHeart(Vector2 position);
void DrawBall(Vector2 position);
void DrawRock(Vector2 position);
void DrawBlock(Vector2 position);
void DrawDoor(Vector2 position, int signal);
void DrawMenuBackground(Vector2 position);
void DrawMap(pGame_map map);

#endif
