#pragma once

#include <stdbool.h>

#include "entity.h"
#include "position.h"

#define TILE_WALL                   '#'
#define TILE_FLOOR                  '.'
#define TILE_NONE                   ' '
#define TILE_DOWNSTAIRS             '>'

typedef struct {
    char ch;
    int color;
    bool walkable;
    bool transparent;
    bool visible;
    bool seen;
    Entity* monster;
} Tile;

Tile** createMapTiles(void);
Position setupMap(void);
bool isTileFreeForMonster(int y, int x);
void freeMap(void);

extern const int MAP_HEIGHT;
extern const int MAP_WIDTH;
extern Tile** map;