#include <ncurses.h>
#include <stdlib.h>

#include "dungeon.h"
#include "entity.h"
#include "colors.h"
#include "fight.h"
#include "fov.h"
#include "keys.h"
#include "map.h"
#include "message.h"

Entity* createPlayer(Position startPos) {
    Entity* player = calloc(1, sizeof(Entity));
    PlayerInfo* info = calloc(1, sizeof(PlayerInfo));

    player->name = "Player";
    player->hp = 10;
    player->ch = ENTITY_PLAYER;
    player->color = COLOR_PAIR(VISIBLE_COLOR);
    player->strength = 3;
    player->pos = startPos;

    info->dungeonLevel = 1;

    player->playerInfo = info;

    return player;
}

void handleInput(int input) {
    Position newPos = player->pos;

    clearInfoMessage();

    switch (input) {
        case KEY_MOVE_LEFT:
            newPos.x--;
            break;

        case KEY_MOVE_DOWN:
            newPos.y++;
            break;

        case KEY_MOVE_UP:
            newPos.y--;
            break;

        case KEY_MOVE_RIGHT:
            newPos.x++;
            break;

        case KEY_GO_DOWNSTAIRS:
            if (map[player->pos.y][player->pos.x].ch == TILE_DOWNSTAIRS) {
                nextLevel();
            } else {
                setInfoMessage("There are no stairs here.");
            }
            break;

        default:
            break;
    }

    for (int i = 0; i < monsterCount; i++) {
        if (monsters[i] && monsters[i]->pos.x == newPos.x && monsters[i]->pos.y == newPos.y) {
            playerAttackEnemy(player, monsters[i]);
        }
    }

    if (player->pos.x != newPos.x || player->pos.y != newPos.y) {
        movePlayer(newPos);
    }
}

void movePlayer(Position newPos) {
    if (!isInMap(newPos.y, newPos.x)) {
        return;
    }

    if (map[newPos.y][newPos.x].walkable && !map[newPos.y][newPos.x].monster) {
        clearFOV(player);
        player->pos = newPos;
        makeFOV(player);
    }
}