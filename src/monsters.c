#include "colors.h"
#include "entity.h"
#include "map.h"
#include "position.h"
#include <ncurses.h>
#include <stdlib.h>

static const MonsterDefinition monsterDefinitions[] = {
    [BAT]                   = {ENTITY_BAT, 1},
    [DRAGON]                = {ENTITY_DRAGON, 8},
    [GOBLIN]                = {ENTITY_GOBLIN, 2},
    [HAND]                  = {ENTITY_HAND, 1},
    [ROBOT]                 = {ENTITY_ROBOT, 5},
    [SKELETON]              = {ENTITY_SKELETON, 3},
    [TROLL]                 = {ENTITY_TROLL, 6},
    [ZOMBIE]                = {ENTITY_ZOMBIE, 3}
};

Entity* createMonster(MonsterType type, Position startPos) {
    Entity* monster = calloc(1, sizeof(Entity));
    MonsterInfo* info = calloc(1, sizeof(MonsterInfo));

    monster->pos = startPos;
    monster->color = COLOR_PAIR(VISIBLE_COLOR);
    monster->ch = monsterDefinitions[type].ch;

    info->visible = false;

    monster->monsterInfo = info;

    return monster;
}

bool monsterCanSpawn(MonsterType t, int dungeonLevel) {
    return monsterDefinitions[t].minSpawnDungeonLevel <= dungeonLevel;
}

MonsterType pickMonster(int dungeonLevel) {
    MonsterType t;
    int attempts = 0;
    
    do {
        t = rand() % MONSTER_TYPE_COUNT;
        attempts++;
    } while (!monsterCanSpawn(t, dungeonLevel) && attempts < 100);

    return t;
}

void spawnMonsters(int dungeonLevel) {
    int targetCount = 3 + rand() % (2 + dungeonLevel);
    int attempts = 0;
    int y, x;
    MonsterType type;
    Entity* monster;
    Position startPos;

    while (monsterCount < targetCount && attempts < 500) {
        attempts++;
        y = rand() % MAP_HEIGHT;
        x = rand() % MAP_WIDTH;
        if (!isTileFreeForMonster(y, x)) {
            continue;
        }
        type = pickMonster(dungeonLevel);
        startPos.y = y;
        startPos.x = x;
        monster = createMonster(type, startPos);
        if (!monster) {
            continue;
        }

        monsters[monsterCount++] = monster;
        map[y][x].monster = monster;
    }
}