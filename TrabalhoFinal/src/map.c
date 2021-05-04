
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "globals.h"


//Função para debug
void PrintMap_ASCII(pGame_map map){
    int i, j;
    char c;
    pTurf T;
    for(i = 0; i < map->bounds_y; i++){
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

int StrToDir(char* str){
    switch(str[0]){
        case 'W':
            return WEST;
        case 'E':
            return EAST;
        case 'S':
            return SOUTH;
        default:
            return NORTH;
    }
}

void MapFreeMobs(pGame_map map){
    for(; map->n_mobs > 0; map->n_mobs--){
        map->mobs[map->n_mobs].movement_pattern = NULL; //Os padrões de movimento são dealocados em outra função
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
        map->mobs = (pMob) malloc(sizeof(mob) * (amount + 1)); //+ 1 para o jogador
    }
}

void MapCreateItemV(pGame_map map, int amount){
    map->n_items = amount;
    if(map->items != NULL){
        MapFreeMobs(map);
    }
    if(amount > 0){
        map->items = (pItem) malloc(sizeof(item) * (amount + 1)); //+ 1 para a saída
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

void MapCreateMovementPatterns(pGame_map map, int amount){
    map->n_mpatterns = amount;
    if(map->movement_patterns != NULL){
        free(map->movement_patterns);
    }
    if(amount > 0){
        map->movement_patterns = (pMob_movement) malloc(sizeof(mob_movement) * amount);
    }
}

void MapFreeMap(pGame_map map){
    MapFreeMobs(map);
    free(map->movement_patterns);
    free(map->items);
    free(map->turfs);

}

void MapCreateMap(pGame_map map, int bx, int by, int nm, int ni, int np){
    map->bounds_x = bx;
    map->bounds_y = by;
    MapCreateMobV(map, nm);
    MapCreateMovementPatterns(map, np);
    MapCreateItemV(map, ni);
    MapCreateTurfs(map);

}

int LoadMobTypes(char* filename){
    FILE* mob_file;
    if(!(mob_file = fopen(filename, "r"))){
        return 0;
    }
    free(mob_types);


    char amnt_buffer[5];
    int i = 0;
    while(fgets(amnt_buffer, 5, mob_file) != NULL){
        i++;
    }
    rewind(mob_file);

    mob_type_amount = i / 3;
    printf("Lendo [%d] criaturas do arquivo: %s\n", mob_type_amount,  filename);

    if(mob_type_amount){
        mob_types = (pMob) malloc(sizeof(mob) * mob_type_amount);
        pMob M;
        //Lê os mobs: Vida; Icone; Facção;
        for(i = 0; i < mob_type_amount; i++){
            M = &mob_types[i];

            fseek(mob_file, 2, SEEK_CUR);
            fgets(amnt_buffer, 3, mob_file);
            M->health = atoi(amnt_buffer);

            fseek(mob_file, 2, SEEK_CUR);
            fgets(amnt_buffer, 3, mob_file);
            M->icon = atoi(amnt_buffer);

            fseek(mob_file, 2, SEEK_CUR);
            fgets(amnt_buffer, 3, mob_file);
            M->faction = atoi(amnt_buffer);

            printf("Nova criatura [%d]: Vida=%d Icone=%d Faccao=%d\n", i, M->health, M->icon, M->faction);
        }
    }
    fclose(mob_file);
    return 1;
}

int LoadMap(char* filename){
    FILE* map_file;
    if(!(map_file = fopen(filename, "r"))){
        return 0;
    }
    //puts("Carregando o mapa...");
    int i = 0, j, bounds_x, bounds_y, n_mobs = 0, n_keys = 0, n_patterns = 0, n_movables = 0, n_water = 0;
    char map_buffer[MAP_MAX_X], *substr;

    //Carrega informacoes para gerar o mapa basico
    while(fgets(map_buffer, MAP_MAX_X, map_file)){
        if(map_buffer == NULL || *map_buffer == '\n'){
            break;
        }
        n_patterns++;
    }
    fseek(map_file, 1, SEEK_CUR); //Pula \n

    while(fgets(map_buffer, MAP_MAX_X, map_file)){
        if(map_buffer == NULL || *map_buffer == '\n'){
            break;
        }
        n_mobs++;
    }

    //printf("Padroes:%d Mobs:%d\n", n_patterns, n_mobs);

    fgets(map_buffer, MAP_MAX_X, map_file);

    bounds_x = atoi(strtok(map_buffer, ";"));
    bounds_y = atoi(strtok(NULL, ";"));
    n_keys = atoi(strtok(NULL, ";"));
    n_movables = atoi(strtok(NULL, ";")); //Blocos móveis
    n_water = atoi(strtok(NULL, ";")); //Água

    //printf("Limites:%d|%d\n", bounds_x, bounds_y);
    //printf("Chaves:%d Moveis:%d Agua:%d\n", n_keys, n_movables, n_water);

    MapCreateMap(&cur_map, bounds_x, bounds_y, (n_mobs + n_movables), (n_keys + n_water), n_patterns);
    rewind(map_file);

    //puts("Lendo informacoes...");
    //Le informações dos padrões de movimento das criaturas
    pMob_movement MM;
    pMovement_command MC;
    while(fgets(map_buffer, MAP_MAX_X, map_file)){
        if(map_buffer == NULL || *map_buffer == '\n'){
            break;
        }
        //puts("Lendo padrao...");
        puts(map_buffer);
        MM = &cur_map.movement_patterns[i];
        MM->type = atoi(strtok(map_buffer + 2, ";")); //Tipo de padrão
        while((substr = strtok(NULL, ";")) != NULL){
            MC = &MM->commands[i];
            MC->amount = atoi(substr);
            MC->dir = StrToDir(strtok(NULL, ";"));
        }
        i++;
    }
    i = 0;
    //Le informações das criaturas
    pMob M;
    while(fgets(map_buffer, MAP_MAX_X, map_file)){
        if(map_buffer == NULL || *map_buffer == '\n'){
            break;
        }
        //puts("Lendo criatura");
        M = &cur_map.mobs[i];
        *M = mob_types[atoi(strtok(map_buffer + 2, ";"))]; //Copia os dados do tipo
        substr = strtok(NULL, ";");
        if(substr != NULL){
            M->movement_pattern = &cur_map.movement_patterns[atoi(substr)]; //Aponta para um padrão de movimento
        }
        else{
            M->movement_pattern = NULL;
        }
        i++;
    }
    fgets(map_buffer, MAP_MAX_X, map_file); //Pula dados do mapa
    fseek(map_file, 2, SEEK_CUR);//Pula \n
    //Popula o mapa
    pTurf T;
    pItem I;
    char map_c;
    int keys_placed = 0, movables_placed = 0, water_placed = 0, pos;
    for(j = 0; j < bounds_y ; j++){
        for(i = 0; i < bounds_x; i++){
            T = &pMAP_ACESS_TURF((&cur_map), i, j);
            map_c = fgetc(map_file);
            if(i == 0 || j == 0 || i == (bounds_x - 1) || j == (bounds_y - 1)){
                T->solid = 1;
            }
            else{
                if(map_c == '.'){
                    continue;
                }
                if(map_c >= 'a' && map_c <= 'z'){
                    pos = CHAR2MOB_I(map_c);
                    M = &cur_map.mobs[pos];
                    SetMobPos(M, i, j);
                    M->id = pos;
                }
                else if(map_c == '@'){
                    pos = n_mobs + movables_placed++;
                    M = &cur_map.mobs[pos];
                    SetMobPos(M, i, j); //Blocos moveis sao as ultimas criaturas do vetor sempre
                    M->id = pos;
                }
                else if(map_c == 'P'){
                    M = &cur_map.mobs[0]; //Jogador sempre é a primeira criatura
                    SetMobPos(M, i, j);
                    M->id = PLAYER_ID;
                }
                else if(map_c == '*'){
                    pos = keys_placed++;
                    I = &cur_map.items[pos];
                    SetItemPos(I, i, j);
                    I->id = pos;
                    //Chamar função que define item como chave (coração)
                }
                else if(map_c == '='){
                    pos = n_keys + water_placed++;
                    I = &cur_map.items[pos];
                    SetItemPos(I, i, j); //Água vem depois das Chaves (Corações) no vetor
                    I->id = pos;
                    //Chamar função que define item como agua
                }
                else if(map_c == 'B'){
                    pos = n_keys + n_water;
                    I = &cur_map.items[0]; //A saída (Baú) sempre é o último item
                    SetItemPos(I, i, j);
                    I->id = pos;
                    //Chamar função que define item como porta
                }
            }
        }
        fseek(map_file, 2, SEEK_CUR); //Pula \n
    }

    fclose(map_file);
    return 1;
}
