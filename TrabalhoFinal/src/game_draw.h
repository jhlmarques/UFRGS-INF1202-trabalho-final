#ifndef _game_draw_h_
#define _game_draw_h_

#include "raylib.h"
#include "map.h"
#include "menu.h"

#define TEXTURE_EXISTS(I) (I <= texture_amount && I > 0)

void LoadGameTextures(char* textures_file_name);

void UnloadGameTextures();

void DrawMenu(pMenu game_menu);

void DrawMob(pMob M);

void DrawItem(pItem I);

void DrawTurf(pTurf T);

void DrawInfo();

void DrawGame();


#endif