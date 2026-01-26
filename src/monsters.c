#include "colors.h"
#include "entity.h"
#include "map.h"
#include "position.h"
#include <ncurses.h>
#include <stdlib.h>

static const MonsterDefinition monsterDefinitions[] = {
    [BAT]                   = {"Bat", ENTITY_BAT, 4, 1, 1, 3},
    [DRAGON]                = {"Dragon", ENTITY_DRAGON, 100, 20, 8, 10},
    [GOBLIN]                = {"Goblin", ENTITY_GOBLIN, 10, 3, 2, 5},
    [HAND]                  = {"Floating Hand", ENTITY_HAND, 4, 2, 1, 2},
    [ROBOT]                 = {"Robot", ENTITY_ROBOT, 30, 6, 5, 6},
    [SKELETON]              = {"Skeleton", ENTITY_SKELETON, 10, 3, 3, 4},
    [TROLL]                 = {"Troll", ENTITY_TROLL, 50, 10, 6, 6},
    [ZOMBIE]                = {"Zombie", ENTITY_ZOMBIE, 10, 3, 3, 3}
};

Entity* createMonster(MonsterType type, Position startPos) {
    Entity* monster = calloc(1, sizeof(Entity));
    MonsterInfo* info = calloc(1, sizeof(MonsterInfo));

    monster->name = monsterDefinitions[type].name;
    monster->hp = monsterDefinitions[type].hp;
    monster->color = COLOR_PAIR(VISIBLE_COLOR);
    monster->ch = monsterDefinitions[type].ch;
    monster->strength = monsterDefinitions[type].strength;
    monster->pos = startPos;

    info->visible = false;
    info->fovRadius = monsterDefinitions[type].fovRadius;

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

        monsters[monsterCount++] = monster;
        map[y][x].monster = monster;
    }
}