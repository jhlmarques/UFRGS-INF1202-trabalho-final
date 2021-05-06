#ifndef _game_h_

#include "mobs.h"

int CheckPaused();

void GameLoop();

void PlayerInput();

void MobAction();

void OnPlayerKilled();

void OnPlayerCollectKey();

void OnLevelEnd();

#endif
