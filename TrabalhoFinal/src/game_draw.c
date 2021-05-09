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
    puts("CARREGANDO TEXTURAS");

    //Texturas basicas, para criaturas/itens/territorios com textura inexistente
    base_mob_texture = LoadTexture(BASE_MOB_TEXTURE_FILE);
    base_item_texture = LoadTexture(BASE_ITEM_TEXTURE_FILE);
    base_turf_texture = LoadTexture(BASE_TURF_TEXTURE_FILE);
    char buffer[100];
    int i = 0, len;
    //Primeira linha do arquivo é a quantidade de texturas no arquivo
    texture_amount = atoi(fgets(buffer, 3, textures_file));
    printf("TEXTURAS: %d\n", texture_amount);
    if(!texture_amount){
        return;
    }

    all_textures = (Texture *) malloc(sizeof(Texture) * texture_amount);

    while(fgets(buffer, 100, textures_file) != NULL){
        len = strlen(buffer);
        if(buffer[len-1] == '\n'){
            buffer[len-1] = '\0';
        }

        all_textures[i] = LoadTexture(buffer);
        if(++i >= texture_amount){
            break;
        }
    }
    puts("TEXTURAS CARREGADAS!");

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

void DrawMob(pMob M){
    if(TEXTURE_EXISTS(M->texture)){
        DrawTexture(all_textures[M->texture - 1], M->pos.x * 32, M->pos.y * 32, WHITE);
    }
    else{
        DrawTexture(base_mob_texture, M->pos.x * 32, M->pos.y * 32, WHITE);
    }
}

void DrawItem(pItem I){
    if(TEXTURE_EXISTS(I->texture)){
        DrawTexture(all_textures[I->texture - 1], I->pos.x * 32, I->pos.y * 32, WHITE);
    }
    else{
        DrawTexture(base_item_texture, I->pos.x * 32, I->pos.y * 32, WHITE);
    }
}

void DrawTurf(pTurf T){
    if(TEXTURE_EXISTS(T->texture)){
        DrawTexture(all_textures[T->texture - 1], T->pos.x * 32, T->pos.y * 32, WHITE);
    }
    else{
        DrawTexture(base_turf_texture, T->pos.x * 32, T->pos.y * 32, WHITE);
    }
}

void DrawGame(){
    int i, j;
    pTurf T;

    for(i = 0; i < cur_map->bounds_y; i++){
        for(j = 0; j < cur_map->bounds_x; j++){
            T = &pMAP_ACESS_TURF(cur_map, j, i);
            //Ordem de desenho: Turf -> Item -> Mob
            //printf("DRAWING TURF (%d,%d)\n", j, i);
            DrawTurf(T);
            if(pTURF_HAS_ITEM(T)){
                //printf("DRAWING ITEM [%d]\n", T->cur_item);
                DrawItem(GetItem(T->cur_item));
            }
            if(pTURF_HAS_MOB(T)){
                //printf("DRAWING MOB [%d]\n", T->cur_mob);
                DrawMob(GetMob(T->cur_mob));
            }
        }
    }

}



