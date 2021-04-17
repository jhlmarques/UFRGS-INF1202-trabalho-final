#include "mobs.h"
#include "defines.h"
#include "globals.h"

int is_alive(pMob mob){
    if(mob->health > 0){
        return 1;
    }
    return 0;
}

pMob get_mob(int mob_id){
    return &cur_map->mobs[mob_id];
}

int can_attack(pMob mob){
    return 1;
}

int push(pMob moved, int direction){
    //if(!can_move(moved, ))
    return 1;
}

//retorna 1 se o atacante venceu, 0 para outros casos
int attack(pMob attacker, pMob attacked){
    if(attacked->invincible){
        if(attacker->invincible){
            return 0;
        }
        return attack(attacked, attacker);
    }
    if(can_attack(attacker)){
        attacked->health--;
        return 1;
    }
    return 0;

}

void simple_move(pMob moved, pTurf dest){
    pTurf cur_turf = get_turf(moved->pos);
    cur_turf->cur_mob = NO_ID;
    dest->cur_mob = moved->id;
}

int move_to_turf(pMob moved, pTurf dest){
    if(pTURF_IS_SOLID(dest)){
        return 0;
    }
    if(pTURF_HAS_MOB(dest)){
        pMob dest_mob = get_mob(dest->cur_mob);
        if(moved->faction == dest_mob->faction || (moved->faction == NEUTRAL && moved->id == PLAYER_ID)){
            if(!push(dest_mob, moved->dir)){
                return 0;
            }
        }
        else if(dest_mob->faction == NEUTRAL){
            return 0;
        }
        else{
            attack(moved, dest_mob);
            if(is_alive(dest_mob)){
                return 0;
            }
       }
    }
    if(pTURF_HAS_ITEM(dest) && pMOB_IS_PLAYER(moved)){
        item_activated(dest->cur_item);
    }

    simple_move(moved, dest);
    return 1;

}
