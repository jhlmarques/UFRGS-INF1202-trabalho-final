#include "game.h"
#include "globals.h"
#include "defines.h"
#include "raylib.h"

int CheckPaused(){
    return IsKeyPressed(KEY_ESCAPE);
}

void GameLoop(){
    if(game_state == STATE_PLAYING){
        PlayerMovementInput();
        MobAction();
    }
}

void PlayerMovementInput(){
    //Movimento
    if(player_mob->action_cooldown > 0){
        player_mob->action_cooldown--;
    }
    else{
        if(IsKeyDown(KEY_RIGHT)){
            player_mob->dir = EAST;
        }
        else if (IsKeyDown(KEY_LEFT)){
            player_mob->dir = WEST;
        }
        else if (IsKeyDown(KEY_UP)){
            player_mob->dir = NORTH;
        }
        else if (IsKeyDown(KEY_DOWN)){
            player_mob->dir = SOUTH;
        }
        else{
            return;
        }
        if(MoveCheckInteractions(player_mob)){
            player_mob->action_cooldown = 10;
        }
    }
}

void MobAction(){
    pMob M;
    pMob_movement MM;
    pMovement_command MC;
    int i;
    for(i = 1; i < cur_map->n_mobs; i++){
        M = cur_map->mobs + i;
        if(!IsAlive(M)){
            continue;
        }
        if(M->action_cooldown > 0){
            M->action_cooldown--;
        }
        else if(M->movement_pattern > -1){
            MM = cur_map->movement_patterns + M->movement_pattern;
            M->action_cooldown = MM->movement_interval;
            MC = &MM->commands[M->cur_movement_command];

            if(M->movement_counter >= MC->amount){
                M->movement_counter = 0;
                M->cur_movement_command = (M->cur_movement_command + 1) >= MM->command_amnt ? 0 : (M->cur_movement_command + 1);
                MC = &MM->commands[M->cur_movement_command];
            }

            M->dir = MC->dir;
            M->movement_counter++;
            MoveCheckInteractions(M);
        }
    }

}

void OnPlayerKilled(){
    if(--cur_save->lives == 0){
        game_state = STATE_STOPPED_PLAYING;
        cur_map->points = 0;
    }
    else{
        SimpleMove(player_mob, GetTurf(cur_map->player_start_pos));
        player_mob->health = 1;
        cur_map->points = 0; //Zera pontos
    }
}

void OnKeyCollected(){
    pItem I = GetItem(cur_map->n_items - 1); //Último item sempre é a saída
    SetItemPos(I, I->pos.x, I->pos.y);    
}

void AddPoints(int amount){
    cur_map->points += amount;
    if(cur_map->points % 10 == 0){
        cur_save->lives++;
        WriteSaveToFile(SAVEFILE_NAME, cur_save, cur_save->save_id);
    }
}

void OnMobKilled(pMob killed){
    if(killed->faction == HOSTILE){
        if(--cur_map->enemies_left == 0){
            pItem I = GetItem(cur_map->n_items - 2); //Penultimo item sempre é a saída
            SetItemPos(I, I->pos.x, I->pos.y);
        }
        AddPoints(POINT_REWARD_ENEMY_DEFEATED);
    }
}

void OnPlayerCollectPower(){
    player_mob->powered++; //Ganha poder;
}

void OnLevelEnd(){
    cur_save->cur_level++;
    cur_save->points = cur_map->points;
    game_state = STATE_LOADING_MAP;
}
