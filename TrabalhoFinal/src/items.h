#ifndef _items_h_
#define _items_h_

#include "point.h"
#include "raylib.h"

typedef struct item{
    Vector2 pos; //Posição
    int type; //Tipo de item
    int texture; //Textura
    int id; //Identificador

}item, *pItem;

//Acessa o mapa atual e retorna o item de id igual ao fornecido
pItem GetItem(int item_id);

//Lógica pós contato do jogador com item
void ItemTouched(int item_id);

//Põe item na posição x,y do mapa atual
void SetItemPos(pItem I, int x, int y);

#endif
