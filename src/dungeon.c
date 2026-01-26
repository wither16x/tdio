#include "dungeon.h"
#include "message.h"
#include "map.h"
#include "entity.h"

void nextLevel(void) {
    clearInfoMessage();
    setInfoMessage("You go downstairs...");

    freeMap();

    map = createMapTiles();
    player->pos = setupMap();
    player->playerInfo->dungeonLevel++;

    setInfoMessage("You go down the stairs...");
    spawnMonsters(player->playerInfo->dungeonLevel);
    setPlayerStatsMessage("Dungeon level: %d", player->playerInfo->dungeonLevel);
}