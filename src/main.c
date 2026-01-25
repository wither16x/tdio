#include <stddef.h>
#include <ncurses.h>

#include "entity.h"
#include "map.h"
#include "engine.h"
#include "message.h"

const int MAP_HEIGHT = 25;
const int MAP_WIDTH = 80;

Entity* player;
Entity* monsters[MAX_MONSTERS];
Tile** map;
MessageArea* messageArea;
int monsterCount = 0;

int main(void) {
    bool isTerminalCompatible;

    isTerminalCompatible = cursesSetup();
    if (isTerminalCompatible) {
        gameSetup();
        gameLoop();
        closeGame();
    } else {
        endwin();
    }

    return 0;
}