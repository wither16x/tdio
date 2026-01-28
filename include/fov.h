#pragma once

#include <stdbool.h>

#include "entity.h"
#include "position.h"

void makeFOV(Entity* player);
void clearFOV(Entity* player);
bool monsterSeesPlayer(Entity* monster, Entity* player);
int getDistance(Position origin, Position target);
bool isInMap(int y, int x);
bool lineOfSight(Position origin, Position target);
int getSign(int a);