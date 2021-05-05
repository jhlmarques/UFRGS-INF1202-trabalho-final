#ifndef _turfs_h_
#define _turfs_h_

typedef struct mob *pMob;

#include "mobs.h"
#include "defines.h"
#include "raylib.h"

#define pTURF_HAS_MOB(pTurf) (pTurf->cur_mob > NO_ID)
#define pTURF_IS_SOLID(pTurf) (pTurf->solid)
#define pTURF_HAS_ITEM(pTurf) (pTurf->cur_item > NO_ID)

typedef struct turf{
    int solid; //Criaturas n�o podem se mover para turfs solidos
    int cur_mob; //Criatura atual (id)
    int cur_item; //Item atual (id)
    int faction; //Se n�o neutro, somente criaturas da mesma fac��o (ou neutras) podem passar
    Vector2 pos;

}turf, *pTurf;

void TurfSetPos(pTurf T, float a, float b);

pTurf GetTurf(Vector2 coord);


#endif
