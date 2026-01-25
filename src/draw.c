#include <ncurses.h>

#include "map.h"
#include "colors.h"
#include "entity.h"

void drawMap(void) {
    char ch;
    int color;

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (map[y][x].visible) {
                ch = map[y][x].ch;
                color = map[y][x].color;
            } else if (map[y][x].seen) {
                ch = map[y][x].ch;
                color = COLOR_PAIR(SEEN_COLOR);
            } else {
                ch = TILE_NONE;
                color = 0;
            }

            mvaddch(y, x, ch | color);

            Entity* m = map[y][x].monster;
            if (m && m->monsterInfo->visible) {
                mvaddch(y, x, m->ch | m->color);
            }
        }
    }
}

void drawEntity(Entity* entity) {
    mvaddch(entity->pos.y, entity->pos.x, entity->ch | entity->color);
}

void draw(void) {
    clear();
    drawMap();
    drawEntity(player);
}