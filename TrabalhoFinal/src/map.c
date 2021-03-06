
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
    pMob M;
    pItem I;
    for(i = 0; i < map->bounds_y; i++){
        for(j = 0; j < map->bounds_x; j++){
            T = &pMAP_ACESS_TURF(map, j, i);
            if(pTURF_IS_SOLID(T)){
                c = ASCII_TURF_SOLID;
            }
            else if(pTURF_HAS_MOB(T) || pTURF_HAS_ITEM(T)){
                if(!pTURF_HAS_ITEM(T)){
                    M = GetMob(T->cur_mob);
                    switch(M->faction){
                        case NEUTRAL:
                        c = ASCII_TURF_HAS_NEUTRAL;
                        break;
                        case FRIENDLY:
                        if(pMOB_IS_PLAYER(M)){
                            c = ASCII_TURF_HAS_PLAYER;
                        }
                        else{
                            c = ASCII_TURF_HAS_FRIENDLY;
                        }
                        break;
                        case HOSTILE:
                        c = ASCII_TURF_HAS_HOSTILE;
                        break;
                    }
                }
                else if(!pTURF_HAS_MOB(T)){
                    I = GetItem(T->cur_item);
                    switch(I->type){
                        case ITEM_KEY:
                        c = ASCII_TURF_HAS_KEY;
                        break;
                        case ITEM_WATER:
                        c = ASCII_TURF_HAS_WATER;
                        break;
                        case ITEM_EXIT:
                        c = ASCII_TURF_HAS_DOOR;
                        break;
                    }
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
    map->n_items = amount + 2;
    if(amount > 0){
        map->items = (pItem) malloc(sizeof(item) * map->n_items); //+ 2 para a chave e a saída
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

void MapCreateMovementPatternV(pGame_map map, int amount){
    map->n_mpatterns = amount;
    if(amount > 0){
        map->movement_patterns = (pMob_movement) malloc(sizeof(mob_movement) * amount);
    }
}

void MapFreeElements(pGame_map map){
    free(map->turfs);
    map->turfs = NULL;
    free(map->items);
    map->items = NULL;
    free(map->mobs);
    map->mobs = NULL;
    free(map->movement_patterns);
    map->movement_patterns = NULL;
}

void SetMap(pGame_map map, int bx, int by, int nm, int ni, int np, int nenemies){
    map->bounds_x = bx;
    map->bounds_y = by;
    MapCreateMobV(map, nm);
    MapCreateMovementPatternV(map, np);
    MapCreateItemV(map, ni);
    MapCreateTurfs(map);
    map->enemies_left = nenemies;
    map->points = 0;
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
        //Lê os mobs: Vida; Textura; Facção;
        for(i = 0; i < mob_type_amount; i++){
            M = &mob_types[i];

            fseek(mob_file, 2, SEEK_CUR);
            fgets(amnt_buffer, 3, mob_file);
            M->health = atoi(amnt_buffer);

            fseek(mob_file, 2, SEEK_CUR);
            fgets(amnt_buffer, 3, mob_file);
            M->texture = atoi(amnt_buffer);

            fseek(mob_file, 2, SEEK_CUR);
            fgets(amnt_buffer, 3, mob_file);
            M->faction = atoi(amnt_buffer);
        }
    }
    fclose(mob_file);
    return 1;
}

int PopulateMap(char* filename, pGame_map map){
    FILE* map_file;
    if(!(map_file = fopen(filename, "r"))){
        return 0;
    }
    int i = 0, j, bounds_x, bounds_y, n_mobs = 0, n_powers = 0, n_patterns = 0, n_movables = 0, n_hazards = 0;
    int turf_open_texture, turf_closed_texture, texture_hazard, texture_movables, texture_power, texture_key, texture_exit;
    int positions_to_skip = 0; //argumento para fseek, para pular direto ao mapa após a leitura dos outros dados
    char map_buffer[MAP_MAX_X], *substr;

    //Carrega informacoes para gerar o mapa basico
    while(fgets(map_buffer, MAP_MAX_X, map_file)){
        positions_to_skip += strlen(map_buffer) + 1; //Embora \n é capturado, strlen conta como 1 caractere, quando de fato é 2
        if(map_buffer == NULL || *map_buffer == '\n'){
            break;
        }
        n_patterns++;
    }

    while(fgets(map_buffer, MAP_MAX_X, map_file)){
        positions_to_skip += strlen(map_buffer) + 1; 
        if(map_buffer == NULL || *map_buffer == '\n'){
            break;
        }
        n_mobs++;
    }
    //Outros dados do mapa
    positions_to_skip += strlen(fgets(map_buffer, MAP_MAX_X, map_file)) + 1; //Limites do mapa

    bounds_x = atoi(strtok(map_buffer, ";"));
    bounds_y = atoi(strtok(NULL, ";"));

    positions_to_skip += strlen(fgets(map_buffer, MAP_MAX_X, map_file)) + 1;

    turf_open_texture = atoi(strtok(map_buffer, ";")); //Textura das turfs abertas
    turf_closed_texture = atoi(strtok(NULL, ";")); //Textura das turfs fechadas

    positions_to_skip += strlen(fgets(map_buffer, MAP_MAX_X, map_file)) + 1;

    n_movables = atoi(strtok(map_buffer, ";")); //Blocos móveis
    texture_movables = atoi(strtok(NULL, ";"));

    positions_to_skip += strlen(fgets(map_buffer, MAP_MAX_X, map_file)) + 1;

    n_hazards = atoi(strtok(map_buffer, ";")); //Abismos/agua/etc
    texture_hazard = atoi(strtok(NULL, ";"));

    positions_to_skip += strlen(fgets(map_buffer, MAP_MAX_X, map_file)) + 1;

    n_powers = n_mobs; //Poderes
    texture_power = atoi(strtok(map_buffer, ";"));

    positions_to_skip += strlen(fgets(map_buffer, MAP_MAX_X, map_file)) + 1; //Chave

    texture_key = atoi(strtok(map_buffer, ";"));

    positions_to_skip += strlen(fgets(map_buffer, MAP_MAX_X, map_file)) + 1; //Saida

    texture_exit = atoi(strtok(map_buffer, ";"));

    positions_to_skip += 2; //Ultimo \n

    SetMap(map, bounds_x, bounds_y, (n_mobs + n_movables), (n_powers + n_hazards), n_patterns, n_mobs);
    rewind(map_file);

    //Le informações dos padrões de movimento das criaturas
    pMob_movement MM;
    pMovement_command MC;
    while(fgets(map_buffer, MAP_MAX_X, map_file)){
        if(map_buffer == NULL || *map_buffer == '\n'){
            break;
        }
        MM = &map->movement_patterns[i];
        MM->movement_interval = atoi(strtok(map_buffer + 2, ";")); //Intervalo de movimento
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
        SetBasicMob(M, MT->health, MT->texture, MT->faction);
        substr = strtok(NULL, ";");
        if(*substr != '\n'){
            M->movement_pattern = atoi(substr); //Guarda o numero do padrao de movimento no vetor do mapa
        }
        else{
            M->movement_pattern = -1;
        }
        i++;
    }

    fseek(map_file, positions_to_skip, SEEK_SET); //Pula dados do mapa irrelevantes

    //Popula o mapa
    pTurf T;
    pItem I;
    char map_c;
    int keys_placed = 0, movables_placed = 0, hazards_placed = 0, pos;
    for(j = 0; j < bounds_y ; j++){
        for(i = 0; i < bounds_x; i++){
            T = &pMAP_ACESS_TURF(map, i, j);
            map_c = fgetc(map_file);
            if(i == 0 || j == 0 || i == (bounds_x - 1) || j == (bounds_y - 1)){
                T->solid = 1;
                T->texture = turf_closed_texture;
            }
            else{
                T->texture = turf_open_texture;
                if(map_c == '.'){
                    continue;
                }
                if(map_c >= 'a' && map_c <= 'z'){
                    pos = CHAR2MOB_I(map_c); //Criaturas comuns ja sao definidas basicamente na etapa anterior
                    M = &map->mobs[pos];
                    M->id = pos;
                    SetMobPos(M, i, j);
                }
                else if(map_c == '@'){
                    pos = 1 + n_mobs + movables_placed++;
                    M = &map->mobs[pos];
                    M->id = pos;
                    SetMobPos(M, i, j); //Blocos moveis sao as ultimas criaturas do vetor sempre
                    SetBasicMob(M, 1, texture_movables, NEUTRAL);
                    M->movement_pattern = -1;
                }
                else if(map_c == 'P'){
                    M = &map->mobs[0]; //Jogador sempre é a primeira criatura
                    M->id = PLAYER_ID;
                    SetMobPos(M, i, j);
                    SetBasicMob(M, 1, TEXTURE_PLAYER, FRIENDLY);
                    map->player_start_pos = M->pos;
                }
                else if(map_c == '*'){
                    pos = keys_placed++;
                    I = &map->items[pos];
                    I->id = pos;
                    SetItemPos(I, i, j);
                    I->type = ITEM_POWER;
                    I->texture = texture_power;
                }
                else if(map_c == '='){
                    pos = n_powers + hazards_placed++;
                    I = &map->items[pos];
                    I->id = pos;
                    I->texture = texture_hazard;
                    SetItemPos(I, i, j); //Água vem depois dos Corações no vetor
                    I->type = ITEM_WATER;
                }
                else if(map_c == 'B'){
                    pos = n_powers + n_hazards;
                    I = &map->items[pos]; //A chave sempre é o penúltimo item
                    I->id = pos;
                    I->texture = texture_key;
                    I->pos.x = i; //Não está no mapa
                    I->pos.y = j;
                    I->type = ITEM_KEY;
                }
                else if(map_c == 'D'){
                    pos = n_powers + n_hazards + 1;
                    I = &map->items[pos]; //A saída sempre é o último item
                    I->id = pos;
                    I->texture = texture_exit;
                    I->pos.x = i; //Não está no mapa
                    I->pos.y = j;
                    I->type = ITEM_EXIT;
                }
            }
        }
        fseek(map_file, 2, SEEK_CUR); //Pula \n
    }
    fclose(map_file);
    return 1;
}

int PopulateCurMapFromMapList(char* map_list_file, int index){
    FILE* map_list;
    if(!(map_list = fopen(map_list_file, "r"))){
        return 0;
    }
    int i = 0, len;
    char filename_buffer[100];
    while(fgets(filename_buffer, 100, map_list) != NULL){
        if(i == index){
            len = strlen(filename_buffer);
            if(filename_buffer[len - 1] == '\n'){//fgets pode pegar \n se não é o fim do arquivo
                filename_buffer[len - 1] = '\0'; //Encurta a string
            }
            PopulateMap(filename_buffer, cur_map);
            fclose(map_list);
            return 1;
        }
        i++;
    }
    fclose(map_list);
    return 0;
}
