#include "fight.h"
#include "entity.h"
#include "fov.h"
#include "map.h"
#include "message.h"
#include "position.h"
#include <stddef.h>

static int round = 0;

bool canFightStart(Entity *player, Entity *enemy) {
    return monsterSeesPlayer(enemy, player);
}

void performFight(Entity *player, Entity *enemy) {
    if (canFightStart(player, enemy)) {
        enemyTrackPlayer(enemy, player);
        if (getDistance(enemy->pos, player->pos) == 1 || getDistance(enemy->pos, player->pos) == 0) {
            if (round % 2 == 0) {
                playerAttackEnemy(player, enemy);
            } else {
                enemyAttackPlayer(enemy, player);
            }
        }
    }
}

void enemyTrackPlayer(Entity *enemy, Entity *player) {
    Position newPos;
    int dx, dy;

    while (getDistance(enemy->pos, player->pos) > 1) {
        dx = player->pos.x - enemy->pos.x;
        dy = player->pos.y - enemy->pos.y;

        newPos = enemy->pos;

        if (dx != 0) {
            newPos.x += (dx > 0 ? 1 : -1);
        }
        if (dy != 0) {
            newPos.y += (dy > 0 ? 1 : -1);
        }

        if (!map[newPos.y][newPos.x].walkable || map[newPos.y][newPos.x].monster != NULL) {
            break;
        }

        moveEntity(enemy, newPos);
    }
}

void playerAttackEnemy(Entity *player, Entity *enemy) {
    enemy->hp -= player->strength;
    setInfoMessage("You hit the %s!", enemy->name);
    round++;
}

void enemyAttackPlayer(Entity *enemy, Entity *player) {
    player->hp -= enemy->strength;
    setInfoMessage("The %s hits you!", enemy->name);
    round++;
}