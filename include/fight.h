#pragma once

#include "entity.h"
#include <stdbool.h>

typedef enum {
    PLAYER_TURN,
    ENEMIES_TURN
} Turn;

void performFight(Entity* player, Entity* enemy);
void enemyTrackPlayer(Entity* enemy, Entity* player);
void playerAttackEnemy(Entity* player, Entity* enemy);
void enemyAttackPlayer(Entity* enemy, Entity* player);

extern Turn currentTurn;