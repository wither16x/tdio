#include "fight.h"
#include "draw.h"
#include "engine.h"
#include "entity.h"
#include "experience.h"
#include "fov.h"
#include "map.h"
#include "message.h"
#include "position.h"
#include <ncurses.h>
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

    if (isPlayerDead()) {
        killPlayer(enemy->name);
        draw();
        getch();
        gameOver();
    }
    if (isEnemyDead(enemy)) {
        for (int i = 0; i < monsterCount; i++) {
            if (monsters[i] == enemy) {
                killEnemy(enemy);
                monsters[i] = NULL;
                break;
            }
        }
        return;
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
    int chances = (rand() % 10) + 1;
    if (chances > 4) {
        enemy->hp -= player->strength;
        appendInfoMessage("You hit the %s! ", enemy->name);
    } else {
        appendInfoMessage("You miss.");
    }
}

void enemyAttackPlayer(Entity *enemy, Entity *player) {
    int chances = (rand() % 10) + 1;
    if (chances > 6) {
        player->hp -= enemy->strength;
        if (player->hp < 0) {
            player->hp = 0;
        }
        appendInfoMessage("The %s hits you! ", enemy->name);
    } else {
        appendInfoMessage("The %s misses.", enemy->name);
    }
}

bool isPlayerDead(void) {
    return player->hp <= 0;
}

bool isEnemyDead(Entity *enemy) {
    return enemy->hp <= 0;
}

void killPlayer(const char *killer) {
    setInfoMessage("You have been killed by a %s.", killer);
}

void killEnemy(Entity *enemy) {
    setInfoMessage("You killed the %s.", enemy->name);
    getExperience(enemy->monsterInfo->xpDrop);
    map[enemy->pos.y][enemy->pos.x].monster = NULL;
    free(enemy->monsterInfo);
    free(enemy);
}

void gameOver(void) {
    clear();
    refresh();
    mvprintw(0, 0, "Press a key...");
    getch();
    closeGame();
}