#include "mobs.h"
#include "defines.h"
#include "globals.h"
#include "raylib.h"
#include "point.h"
#include "game.h"

int IsAlive(pMob mob){
    if(mob->health > 0){
        return 1;
    }
    return 0;
}

pMob GetMob(int mob_id){
    return &cur_map->mobs[mob_id];
}

int CanAttack(pMob attacker, pMob attacked){
    if(attacker->faction == FRIENDLY){
        if(!attacker->powered || attacked->powered){
            return 0;
        }
    }
    return 1;
}

int Push(pMob moved, int direction){
    Vector2 dest_coord;
    dest_coord = PointMoveDir(moved->pos, direction);
    pTurf dest = GetTurf(dest_coord);

    if((pTURF_HAS_MOB(dest)) || (pTURF_IS_SOLID(dest)) || (pTURF_HAS_ITEM(dest))){
        return 0;
    }
    SimpleMove(moved, dest);
    return 1;
}

void OnAttacked(pMob Attacked){
    if(--Attacked->health <= 0){
        pTurf T = GetTurf(Attacked->pos);
        T->cur_mob = NO_ID;
        if(pMOB_IS_PLAYER(Attacked)){
            OnPlayerKilled();
        }
    }
}

//retorna 1 se o atacante venceu, 0 para outros casos
int Attack(pMob Attacker, pMob Attacked){
    if(Attacked->powered){
        if(!Attacker->powered){
            Attack(Attacked, Attacker);
        }
        return 0;
    }
    if(CanAttack(Attacker, Attacked)){
        OnAttacked(Attacked);
        Attacker->powered = MAX(0, Attacker->powered - 1);
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
        pMob dest_mob = GetMob(dest->cur_mob);

        if((moved->faction == dest_mob->faction) || ((dest_mob->faction == NEUTRAL) && pMOB_IS_PLAYER(moved))){
            if(!Push(dest_mob, moved->dir)){
                return 0;
            }
        }
        else if(dest_mob->faction == NEUTRAL){
            return 0;
        }
        else{
            if(Attack(moved, dest_mob)){
                if(!IsAlive(dest_mob)){
                    return 1;
                }
            }
            return 0;
       }
    }
    if(pTURF_HAS_ITEM(dest) && !pMOB_IS_PLAYER(moved)){
        return 0;
    }

    SimpleMove(moved, dest); //Tem que ocorrer antes

    if(pTURF_HAS_ITEM(dest) && pMOB_IS_PLAYER(moved)){
        ItemTouched(dest->cur_item);
    }

    return 1;

}

void SetMobPos(pMob M, int x, int y){
    M->pos.x = x;
    M->pos.y = y;
    pTurf T = GetTurf(M->pos);
    T->cur_mob = M->id;
}

void SetBasicMob(pMob M, int health, int icon, int faction){
    M->health = health;
    M->icon = icon;
    M->faction = faction;
    M->powered = 0;
    M->action_cooldown = 0;
    M->cur_movement_command = 0;
}
