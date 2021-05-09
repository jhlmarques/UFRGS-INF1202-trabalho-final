#ifndef _turfs_h_
#define _turfs_h_

//Para lidar com referência circular
typedef struct mob *pMob;

#include "mobs.h"
#include "defines.h"
#include "raylib.h"

#define pTURF_HAS_MOB(pTurf) (pTurf->cur_mob > NO_ID) //Checa se há uma criatura no território dado
#define pTURF_IS_SOLID(pTurf) (pTurf->solid) //Checa se o território dado é sólido
#define pTURF_HAS_ITEM(pTurf) (pTurf->cur_item > NO_ID) //Checa se há um item no território dado

typedef struct turf{
    int solid; //Criaturas n�o podem se mover para turfs solidos
    int cur_mob; //Criatura atual (id)
    int cur_item; //Item atual (id)
    int texture; //Textura do território
    Vector2 pos; //Coordenada

}turf, *pTurf;

//Define as coordenadas de um território
void TurfSetPos(pTurf T, float a, float b);

//Acessa o mapa atual e retorna o território de coordenada igual a fornecida
pTurf GetTurf(Vector2 coord);


#endif
