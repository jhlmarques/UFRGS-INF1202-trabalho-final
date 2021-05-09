#ifndef _game_draw_h_
#define _game_draw_h_

#include "raylib.h"
#include "map.h"
#include "menu.h"

#define TEXTURE_EXISTS(I) (I <= texture_amount && I > 0)

//Abre um arquivo de texto para leitura dos caminhos
//aos arquivos de imagem a serem usados como texturas
void LoadGameTextures(char* textures_file_name);

//Descarrega todas texturas carregadas pelo jogo
void UnloadGameTextures();

/*

    As funções abaixo devem ser chamadas entre BeginDrawing() e EndDrawing()

*/

//Desenha o menu
void DrawMenu(pMenu game_menu);

//Desenha uma criatura
void DrawMob(pMob M);

//Desenha um item
void DrawItem(pItem I);

//Desenha um território
void DrawTurf(pTurf T);

//Desenha as informações básicas (vida, pontos, poder, fase)
void DrawInfo();

//Desenha o jogo (mobs, items, turfs, info)
void DrawGame();

#endif
