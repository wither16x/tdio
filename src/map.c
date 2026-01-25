#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>

#include "map.h"
#include "colors.h"
#include "entity.h"
#include "room.h"

Tile** createMapTiles(void) {
    Tile** tiles = calloc(MAP_HEIGHT, sizeof(Tile*));

    for (int y = 0; y < MAP_HEIGHT; y++) {
        tiles[y] = calloc(MAP_WIDTH, sizeof(Tile));
        for (int x = 0; x < MAP_WIDTH; x++) {
            tiles[y][x].ch = TILE_WALL;
            tiles[y][x].color = COLOR_PAIR(VISIBLE_COLOR);
            tiles[y][x].walkable = false;
            tiles[y][x].transparent = false;
            tiles[y][x].visible = false;
            tiles[y][x].seen = false;
        }
    }

    return tiles;
}

Position setupMap(void) {
    int y, x, height, width, nrooms, stairRoom;
    int counter = 0;
    nrooms = (rand() % 9) + 5;
    Room* rooms = calloc(nrooms, sizeof(Room));
    Room r;
    Position startPos, stairPos;

    for (int i = 0; i < nrooms; i++) {
        y = (rand() % (MAP_HEIGHT - 10)) + 1;
        x = (rand() % (MAP_WIDTH - 20)) + 1;
        height = (rand() % 9) + 3;
        width = (rand() % 15) + 5;

        if (!roomOverlaps(rooms, counter, y, x, height, width)) {
            rooms[counter] = createRoom(y, x, height, width);
            addRoomToMap(rooms[counter]);

            if (counter > 0) {
                connectRoomCenters(rooms[counter - 1].center, rooms[counter].center);
            }

            counter++;
        }
    }

    if (counter == 0) {
        free(rooms);
        return setupMap();
    }

    startPos.y = rooms[0].center.y;
    startPos.x = rooms[0].center.x;

    do {
        stairRoom = rand() % counter;
        r = rooms[stairRoom];
        stairPos.y = (rand() % (r.height - 2)) + r.pos.y + 1;
        stairPos.x = (rand() % (r.width - 2)) + r.pos.x + 1;
    } while (stairPos.y == startPos.y && stairPos.x == startPos.x);
    map[stairPos.y][stairPos.x].ch = TILE_DOWNSTAIRS;
    map[stairPos.y][stairPos.x].walkable = true;
    map[stairPos.y][stairPos.x].transparent = true;

    free(rooms);

    return startPos;
}

bool isTileFreeForMonster(int y, int x) {
    if (!map[y][x].walkable) {
        return false;
    }

    if (player && player->pos.y == y && player->pos.x == x) {
        return false;
    }

    for (int i = 0; i < monsterCount; i++) {
        if (monsters[i]->pos.y == y && monsters[i]->pos.x == x) {
            return false;
        }
    }

    return true;
}

void freeMap(void) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        free(map[y]);
    }
    free(map);
}