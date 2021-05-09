#ifndef _game_h_

#include "mobs.h"

//Checa se o jogador quer pausar o jogo
int CheckPaused();

//Executa as funções vitais do jogo
void GameLoop();

//Recebe input do player para movimentação
void PlayerMovementInput();

//Lida com as ações agendadas das criaturas (excluindo o jogador)
void MobAction();

//Lógica pós morte do jogador
void OnPlayerKilled();

//Adiciona pontos
void AddPoints(int amount);

//Lógica ao coletar a chave
void OnKeyCollected();

//Lógica pós morte de criatura (excluindo o jogador)
void OnMobKilled(pMob killed);

//Lógica da adquirição de poder
void OnPlayerCollectPower();

//Lógica do fim da fase
void OnLevelEnd();

#endif
