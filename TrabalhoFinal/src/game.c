#include "game.h"
#include "globals.h"
#include "defines.h"
#include "raylib.h"

int CheckPaused(){
    return IsKeyPressed(KEY_ESCAPE);
}

void GameLoop(pMob player_mob){
    if(game_state == STATE_PLAYING){
        PlayerInput(player_mob);
        MobAction();

    }
}

void PlayerInput(pMob player_mob){
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
            player_mob->action_cooldown = 2;
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
