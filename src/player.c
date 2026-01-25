#include <ncurses.h>
#include <stdlib.h>

#include "entity.h"
#include "colors.h"
#include "fov.h"
#include "keys.h"
#include "map.h"
#include "message.h"

Entity* createPlayer(Position startPos) {
    Entity* player = calloc(1, sizeof(Entity));
    PlayerInfo* info = calloc(1, sizeof(PlayerInfo));

    player->pos = startPos;
    player->ch = ENTITY_PLAYER;
    player->color = COLOR_PAIR(VISIBLE_COLOR);

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
                setInfoMessage("You go downstairs...");
                freeMap();
                map = createMapTiles();
                player->pos = setupMap();
                player->playerInfo->dungeonLevel++;
                setInfoMessage("You go down the stairs...");
                spawnMonsters(player->playerInfo->dungeonLevel);
                setPlayerStatsMessage("Dungeon level: %d", player->playerInfo->dungeonLevel);
            } else {
                setInfoMessage("There are no stairs here.");
            }
            break;

        default:
            break;
    }

    movePlayer(newPos);
}

void movePlayer(Position newPos) {
    if (!isInMap(newPos.y, newPos.x)) {
        return;
    }

    if (map[newPos.y][newPos.x].walkable) {
        clearFOV(player);
        player->pos.x = newPos.x;
        player->pos.y = newPos.y;
        makeFOV(player);
    }
}