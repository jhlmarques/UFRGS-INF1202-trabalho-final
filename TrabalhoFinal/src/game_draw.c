#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#include "defines.h"
#include "globals.h"
#include "menu.h"
#include "mobs.h"
#include "map.h"
#include "items.h"
#include "turfs.h"
#include "game_draw.h"


void LoadGameTextures(char* textures_file_name){
    FILE* textures_file;
    if(!(textures_file = fopen(textures_file_name, "r"))){
        puts("ERRO AO ABRIR ARQUIVO DE TEXTURAS");
        return;
    }

    //Texturas basicas, para criaturas/itens/territorios com textura inexistente
    base_mob_texture = LoadTexture(BASE_MOB_TEXTURE_FILE);
    base_item_texture = LoadTexture(BASE_ITEM_TEXTURE_FILE);
    base_turf_texture = LoadTexture(BASE_TURF_TEXTURE_FILE);
    char buffer[100];
    int i = 0, len;

    texture_amount = 0;
    //Lê quantidade de linhas
    while(fgets(buffer, 100, textures_file) != NULL){
        texture_amount++;
    }
    rewind(textures_file);
    if(!texture_amount){
        return;
    }

    all_textures = (Texture *) malloc(sizeof(Texture) * texture_amount);

    while(fgets(buffer, 100, textures_file) != NULL){
        len = strlen(buffer);
        if(buffer[len-1] == '\n'){ //Arruma o nome do arquivo caso fgets capturou \n
            buffer[len-1] = '\0';
        }

        all_textures[i] = LoadTexture(buffer);
        if(++i >= texture_amount){
            break;
        }
    }

    fclose(textures_file);
}

void UnloadGameTextures(){
    if(texture_amount){
        for(; texture_amount >= 0; texture_amount--){
            UnloadTexture(all_textures[texture_amount]);
        }
    }
    UnloadTexture(base_mob_texture);
    UnloadTexture(base_item_texture);
    UnloadTexture(base_turf_texture);
    free(all_textures);
}

void DrawMenu(pMenu game_menu){
    DrawTexture(all_textures[TEXTURE_MENU_BACKGROUND - 1], 0, 0, WHITE);
    switch(game_menu->state){

        case MAIN_MENU:{
            DrawTexture(all_textures[TEXTURE_GAME_TITLE - 1], 87, 50, WHITE);
            DrawText("NEW GAME\nLOAD GAME\nCREDITS\nEXIT\n", 190, 200, 20, WHITE); 
            DrawCircle(170, 180 + (game_menu->selection * 30), 5.0, WHITE);
            break;
        }
        case MENU_NEWGAME:{
            DrawText(TextFormat("Digite o seu nome (%d/%d)", game_menu->buffer_pos, PLAYER_NAME_LEN - 1), 190, 200, 20, WHITE);
            DrawText(game_menu->input_buffer, 190, 220, 20, WHITE);
            break;
        }
        case MENU_DELETE_SAVE:{
            DrawText("Escolha uma gravação para deletar", 190, 100, 20, RED);
        }
        case MENU_LOADGAME:{
            if(saves_loaded < 0){
                DrawText("Erro ao carregar o arquivo de gravações", 190, 200, 20, WHITE);
            }
            else{
                int i, y_pos = 200;
                pSave_state save;
                DrawText("Escolha uma gravação:", 190, 160, 20, WHITE);
                for(i = 0; i < saves_loaded; i++){
                    save = all_saves + i;
                    DrawText(TextFormat("%d - %s: Fase: %d Vidas: %d Pontos: %d", \
                    save->save_id + 1, save->player_name, save->cur_level, save->lives, save->points),\
                     190, y_pos, 20, ORANGE);
                    y_pos += 30;
                }
                DrawText("Deletar", 190, y_pos, 20, RED);
                if(saves_loaded){
                    DrawCircle(170, 180 + (game_menu->selection * 30), 5.0, WHITE);
                }
            }

            break;
        }
        case MENU_CREDITS:{
            DrawText("CREDITOS\n Jose Henrique Lima Marques\n Matheus Almeida Silva", 190, 200, 20, BLUE);
            break;
        }
        case MENU_PAUSED:{
            DrawText("Voltar ao jogo\nMenu Principal", 190, 180, 20, WHITE);
            DrawCircle(170, 140 + (game_menu->selection * 30), 5.0, WHITE);
            break;
        }
    }

}

void DrawMob(pMob M){
    if(TEXTURE_EXISTS(M->texture)){
        DrawTexture(all_textures[M->texture - 1], M->pos.x * TEXTURE_SIZE, (M->pos.y * TEXTURE_SIZE) + MAP_DRAW_Y_OFFSET, WHITE);
    }
    else{
        DrawTexture(base_mob_texture, M->pos.x * TEXTURE_SIZE, (M->pos.y * TEXTURE_SIZE) + MAP_DRAW_Y_OFFSET, WHITE);
    }
}

void DrawItem(pItem I){
    if(TEXTURE_EXISTS(I->texture)){
        DrawTexture(all_textures[I->texture - 1], I->pos.x * TEXTURE_SIZE, (I->pos.y * TEXTURE_SIZE) + MAP_DRAW_Y_OFFSET, WHITE);
    }
    else{
        DrawTexture(base_item_texture, I->pos.x * TEXTURE_SIZE, (I->pos.y * TEXTURE_SIZE) + MAP_DRAW_Y_OFFSET, WHITE);
    }
}

void DrawTurf(pTurf T){
    if(TEXTURE_EXISTS(T->texture)){
        DrawTexture(all_textures[T->texture - 1], T->pos.x * TEXTURE_SIZE, (T->pos.y * TEXTURE_SIZE) + MAP_DRAW_Y_OFFSET, WHITE);
    }
    else{
        DrawTexture(base_turf_texture, T->pos.x * TEXTURE_SIZE, (T->pos.y * TEXTURE_SIZE) + MAP_DRAW_Y_OFFSET, WHITE);
    }
}

void DrawInfo(){
    DrawText(TextFormat("VIDA: %d ", cur_save->lives), INFO_X_DRAWPOS, INFO_Y_DRAWPOS, 18, WHITE);
    DrawText(TextFormat("PONTOS: %d ", cur_map->points), INFO_X_DRAWPOS + (4*TEXTURE_SIZE), INFO_Y_DRAWPOS, 18, WHITE);
    DrawText(TextFormat("PODER: %d ", player_mob->powered), INFO_X_DRAWPOS + (8*TEXTURE_SIZE), INFO_Y_DRAWPOS, 18, WHITE);
    DrawText(TextFormat("NIVEL: %d ", cur_save->cur_level + 1), INFO_X_DRAWPOS + (12*TEXTURE_SIZE), INFO_Y_DRAWPOS, 18, WHITE);
}

void DrawGame(){
    int i, j;
    pTurf T;

    DrawInfo();

    for(i = 0; i < cur_map->bounds_y; i++){
        for(j = 0; j < cur_map->bounds_x; j++){
            T = &pMAP_ACESS_TURF(cur_map, j, i);
            //Ordem de desenho: Turf -> Item -> Mob
            DrawTurf(T);
            if(pTURF_HAS_ITEM(T)){
                DrawItem(GetItem(T->cur_item));
            }
            if(pTURF_HAS_MOB(T)){
                DrawMob(GetMob(T->cur_mob));
            }
        }
    }

}



