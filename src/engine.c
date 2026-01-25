#include "engine.h"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "colors.h"
#include "entity.h"
#include "fov.h"
#include "draw.h"
#include "keys.h"
#include "map.h"
#include "message.h"
#include "position.h"

bool cursesSetup(void) {
    initscr();
    noecho();
    curs_set(0);

    if (has_colors()) {
        start_color();
        init_pair(VISIBLE_COLOR, COLOR_WHITE, COLOR_BLACK);
        init_pair(SEEN_COLOR, COLOR_BLUE, COLOR_BLACK);
        return true;
    } else {
        mvprintw(0, 0, "Your terminal does not support colors");
        getch();
        return false;
    }
}

void gameSetup(void) {
    Position startPos;

    srand(time(NULL));
    map = createMapTiles();
    startPos = setupMap();
    player = createPlayer(startPos);
    spawnMonsters(player->playerInfo->dungeonLevel);
    initializeMessageArea();
    setPlayerStatsMessage("Dungeon level: %d", player->playerInfo->dungeonLevel);
}

void gameLoop(void) {
    int ch;

    makeFOV(player);
    draw();
    displayMessageArea();

    while ((ch = getch())) {
        if (ch == KEY_QUIT_GAME) {
            break;
        }

        handleInput(ch);
        draw();
        displayMessageArea();
    }
}

void closeGame(void) {
    endwin();
    free(player->playerInfo);
    free(player);
    for (int i = 0; i < monsterCount; i++) {
        free(monsters[i]->monsterInfo);
        free(monsters[i]);
    }
    free(messageArea);
    freeMap();
}