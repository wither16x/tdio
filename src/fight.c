#include "fight.h"
#include "entity.h"
#include "fov.h"
#include "map.h"
#include "message.h"
#include "position.h"
#include <stddef.h>
#include <stdlib.h>

void performFight(Entity *player, Entity *enemy) {
    int d = getDistance(enemy->pos, player->pos);

    if (monsterSeesPlayer(enemy, player)) {
        enemy->monsterInfo->playerDetected = true;
    }

    if (!enemy->monsterInfo->playerDetected)
        return;

    if (d <= 1) {
        enemyAttackPlayer(enemy, player);
    } else {
        enemyTrackPlayer(enemy, player);
    }
}

void enemyTrackPlayer(Entity *enemy, Entity *player) {
    Position newPos = enemy->pos;
    int dx = player->pos.x - enemy->pos.x;
    int dy = player->pos.y - enemy->pos.y;

    if (abs(dx) > abs(dy)) {
        newPos.x += getSign(dx);
    } else {
        newPos.y += getSign(dy);
    }

    if (map[newPos.y][newPos.x].walkable && !map[newPos.y][newPos.x].monster) {
        moveEntity(enemy, newPos);
    }
}

void playerAttackEnemy(Entity *player, Entity *enemy) {
    enemy->hp -= player->strength;
    appendInfoMessage("You hit the %s! ", enemy->name);
}

void enemyAttackPlayer(Entity *enemy, Entity *player) {
    player->hp -= enemy->strength;
    appendInfoMessage("The %s hits you! ", enemy->name);
}