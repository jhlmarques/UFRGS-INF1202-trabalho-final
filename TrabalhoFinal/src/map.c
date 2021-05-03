
#include <stdio.h>
#include <stdlib.h>
#include "map.h"


//Função para debug
void PrintMap_ASCII(pGame_map map){
    int i, j;
    char c;
    pTurf T;
    for(i = map->bounds_y - 1; i >= 0; i--){ //Para o mapa ter (0,0) no canto inferior esquerdo
        for(j = 0; j < map->bounds_x; j++){
            T = &pMAP_ACESS_TURF(map, j, i);
            if(pTURF_IS_SOLID(T)){
                c = ASCII_TURF_SOLID;
            }
            else if(pTURF_HAS_MOB(T) || pTURF_HAS_ITEM(T)){
                if(!pTURF_HAS_ITEM(T)){
                    c = ASCII_TURF_HAS_MOB;
                }
                else if(!pTURF_HAS_MOB(T)){
                    c = ASCII_TURF_HAS_ITEM;
                }
                else{
                    c = ASCII_TURF_HAS_MOBANDITEM;
                }

            }
            else{
                c = ASCII_TURF_EMPTY;
            }

           printf("%c", c);
        }
        printf("\n");
    }
}

void MapFreeMobs(pGame_map map){
    pMob M;
    for(; map->n_mobs > 0; map->n_mobs--){
        M = &map->mobs[map->n_mobs];
        free(M->movement);
    }
    free(map->mobs);
    map->mobs = NULL;
}

void MapCreateMobV(pGame_map map, int amount){
    map->n_mobs = amount;
    if(map->mobs != NULL){
        MapFreeMobs(map);
    }
    if(amount){
        map->mobs = (pMob) malloc(sizeof(mob) * amount);
    }
}

void MapCreateItemV(pGame_map map, int amount){
    map->n_items = amount;
    if(map->items != NULL){
        MapFreeMobs(map);
    }
    if(amount > 0){
        map->items = (pItem) malloc(sizeof(item) * amount);
    }
}

void MapCreateTurfs(pGame_map map){
    int i, j;
    pTurf T;
    map->turfs = (pTurf) malloc(sizeof(turf) * (map->bounds_y * map->bounds_x));
    for(i = 0; i < map->bounds_y; i++){
        for(j = 0; j < map->bounds_x; j++){
            T = &pMAP_ACESS_TURF(map, j, i);
            TurfSetPos(T, j, i);
            T->cur_mob = NO_ID;
            T->cur_item = NO_ID;
            T->solid = 0;
        }
    }

}

void MapFreeMap(pGame_map map){
    MapFreeMobs(map);
    free(map->items);
    free(map->turfs);

}

void MapCreateMap(pGame_map map, int bx, int by, int nm, int ni){
    map->bounds_x = bx;
    map->bounds_y = by;
    map->mobs = NULL;
    map->items = NULL;
    MapCreateMobV(map, nm);
    MapCreateItemV(map, ni);
    MapCreateTurfs(map);

}

