#include "mobs.h"
#include "defines.h"
#include "globals.h"
#include "raylib.h"
#include "point.h"

int IsAlive(pMob mob){
    if(mob->health > 0){
        return 1;
    }
    return 0;
}

pMob get_mob(int mob_id){
    return &cur_map->mobs[mob_id];
}

int CanAttack(pMob mob){
    return 1;
}

int Push(pMob moved, int direction){
    Vector2 dest_coord = moved->pos;
    dest_coord = PointMoveDir(dest_coord, direction);
    pTurf dest = GetTurf(dest_coord);

    if(pTURF_IS_OCCUPIED(dest)){
        return 0;
    }
    SimpleMove(moved, dest);
    return 1;
}

//retorna 1 se o atacante venceu, 0 para outros casos
int Attack(pMob Attacker, pMob Attacked){
    if(Attacked->invincible){
        if(Attacker->invincible){
            return 0;
        }
        return Attack(Attacked, Attacker);
    }
    if(CanAttack(Attacker)){
        Attacked->health--;
        return 1;
    }
    return 0;

}

void SimpleMove(pMob moved, pTurf dest){
    pTurf cur_turf = GetTurf(moved->pos);
    cur_turf->cur_mob = NO_ID;
    dest->cur_mob = moved->id;
    moved->pos = dest->pos;
}

int MoveCheckInteractions(pMob moved){
    Vector2 dest_coord = moved->pos; //Copia posição
    dest_coord = PointMoveDir(dest_coord, moved->dir); //Move a coordenada baseado na direção
    pTurf dest = GetTurf(dest_coord);

    if(pTURF_IS_SOLID(dest)){
        return 0;
    }
    if(pTURF_HAS_MOB(dest)){
        pMob dest_mob = get_mob(dest->cur_mob);
        if((moved->faction == dest_mob->faction) || (dest_mob->faction == NEUTRAL && moved->id == PLAYER_ID)){
            if(!Push(dest_mob, moved->dir)){
                return 0;
            }
        }
        else if(dest_mob->faction == NEUTRAL){
            return 0;
        }
        else{
            Attack(moved, dest_mob);
            if(IsAlive(dest_mob)){
                return 0;
            }
       }
    }
    if(pTURF_HAS_ITEM(dest) && pMOB_IS_PLAYER(moved)){
        ItemActivated(dest->cur_item);
    }

    SimpleMove(moved, dest);
    return 1;

}

void SetMobPos(pMob M, int x, int y){
    M->pos.x = x;
    M->pos.y = y;
    pTurf T = GetTurf(M->pos);
    T->cur_mob = M->id;
}
