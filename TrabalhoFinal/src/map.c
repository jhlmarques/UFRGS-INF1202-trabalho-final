
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

void MapCreateMobV(pGame_map map, int amount){
    map->n_mobs = amount + 1;
    if(amount > 0){
        map->mobs = (pMob) malloc(sizeof(mob) * map->n_mobs); //+ 1 para o jogador
    }
    else{
        map->mobs = NULL;
    }
}

void MapCreateItemV(pGame_map map, int amount){
    map->n_items = amount + 1;
    if(amount > 0){
        map->items = (pItem) malloc(sizeof(item) * map->n_items); //+ 1 para a saída
    }
    else{
        map->items = NULL;
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
    if(amount > 0){
        map->movement_patterns = (pMob_movement) malloc(sizeof(mob_movement) * amount);
    }
}

void MapFreeMap(pGame_map map){
    free(map->turfs);
    free(map->items);
    free(map->mobs);
    free(map->movement_patterns);
    free(map);

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
        }
    }
    fclose(mob_file);
    return 1;
}

int LoadMap(char* filename, pGame_map map){
    FILE* map_file;
    if(!(map_file = fopen(filename, "r"))){
        return 0;
    }
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

    fgets(map_buffer, MAP_MAX_X, map_file);

    bounds_x = atoi(strtok(map_buffer, ";"));
    bounds_y = atoi(strtok(NULL, ";"));
    n_keys = atoi(strtok(NULL, ";"));
    n_movables = atoi(strtok(NULL, ";")); //Blocos móveis
    n_water = atoi(strtok(NULL, ";")); //Água

    MapCreateMap(map, bounds_x, bounds_y, (n_mobs + n_movables), (n_keys + n_water), n_patterns);
    rewind(map_file);

    //Le informações dos padrões de movimento das criaturas
    pMob_movement MM;
    pMovement_command MC;
    while(fgets(map_buffer, MAP_MAX_X, map_file)){
        if(map_buffer == NULL || *map_buffer == '\n'){
            break;
        }
        MM = &map->movement_patterns[i];
        MM->type = atoi(strtok(map_buffer + 2, ";")); //Tipo de padrão
        MM->movement_interval = atoi(strtok(NULL, ";")); //Intervalo de movimento
        j = 0;
        while((substr = strtok(NULL, ";")) != NULL){
            MC = &MM->commands[j];
            MC->amount = atoi(substr);
            MC->dir = StrToDir(strtok(NULL, ";"));
            j++;
        }
        MM->command_amnt = j;
        i++;
    }
    i = 1;
    //Le informações das criaturas
    pMob M, MT;
    while(fgets(map_buffer, MAP_MAX_X, map_file)){
        if(map_buffer == NULL || *map_buffer == '\n'){
            break;
        }

        M = &map->mobs[i];
        MT = &mob_types[atoi(strtok(map_buffer + 2, ";"))]; //Copia os dados do tipo
        M->health = MT->health;
        M->icon = MT->icon;
        M->faction = MT->faction;
        substr = strtok(NULL, ";");
        if(substr != NULL){
            M->movement_pattern = atoi(substr); //Guarda o numero do padrao de movimento no vetor do mapa
        }
        else{
            M->movement_pattern = -1;
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
            T = &pMAP_ACESS_TURF(map, i, j);
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
                    M = &map->mobs[pos];
                    SetMobPos(M, i, j);
                    M->action_cooldown = 0;
                    M->cur_movement_command = 0;
                    M->id = pos;
                }
                else if(map_c == '@'){
                    pos = 1 + n_mobs + movables_placed++;
                    M = &map->mobs[pos];
                    SetMobPos(M, i, j); //Blocos moveis sao as ultimas criaturas do vetor sempre
                    M->faction = NEUTRAL;
                    M->action_cooldown = 0;
                    M->cur_movement_command = 0;
                    M->movement_pattern = -1;
                    M->id = pos;
                }
                else if(map_c == 'P'){
                    M = &map->mobs[0]; //Jogador sempre é a primeira criatura
                    SetMobPos(M, i, j);
                    M->action_cooldown = 0;
                    M->cur_movement_command = 0;
                    M->faction = FRIENDLY;
                    M->id = PLAYER_ID;
                }
                else if(map_c == '*'){
                    pos = keys_placed++;
                    I = &map->items[pos];
                    SetItemPos(I, i, j);
                    I->id = pos;
                    //Chamar função que define item como chave (coração)
                }
                else if(map_c == '='){
                    pos = n_keys + water_placed++;
                    I = &map->items[pos];
                    SetItemPos(I, i, j); //Água vem depois das Chaves (Corações) no vetor
                    I->id = pos;
                    //Chamar função que define item como agua
                }
                else if(map_c == 'B'){
                    pos = n_keys + n_water;
                    I = &map->items[pos]; //A saída (Baú) sempre é o último item
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
