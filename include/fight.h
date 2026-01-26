#pragma once

#include "entity.h"
#include <stdbool.h>

bool canFightStart(Entity* player, Entity* enemy);
void performFight(Entity* player, Entity* enemy);
void enemyTrackPlayer(Entity* enemy, Entity* player);
void playerAttackEnemy(Entity* player, Entity* enemy);
void enemyAttackPlayer(Entity* enemy, Entity* player);