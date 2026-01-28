#pragma once

#include "position.h"
#include <stdbool.h>

#define MAX_MONSTERS                    128

#define ENTITY_PLAYER                   '@'
#define ENTITY_BAT                      'B'
#define ENTITY_DRAGON                   'D'
#define ENTITY_GOBLIN                   'G'
#define ENTITY_HAND                     'H'
#define ENTITY_ROBOT                    'R'
#define ENTITY_SKELETON                 'S'
#define ENTITY_TROLL                    'T'
#define ENTITY_ZOMBIE                   'Z'

typedef enum {
    BAT,
    DRAGON,
    GOBLIN,
    HAND,
    ROBOT,
    SKELETON,
    TROLL,
    ZOMBIE,
    MONSTER_TYPE_COUNT
} MonsterType;

typedef struct {
    char* name;
    char ch;
    int hp;
    int strength;
    int minSpawnDungeonLevel;
    int fovRadius;
} MonsterDefinition;

typedef struct {
    int dungeonLevel;
} PlayerInfo;

typedef struct {
    bool visible;
    int fovRadius;
    bool playerDetected;
} MonsterInfo;

typedef struct {
    char* name;
    int hp;
    char ch;
    int color;
    int strength;
    Position pos;
    PlayerInfo* playerInfo;
    MonsterInfo* monsterInfo;
} Entity;

Entity* createPlayer(Position startPos);
Entity *createMonster(MonsterType type, Position startPos);
void handleInput(int input);
void movePlayer(Position newPos);
bool monsterCanSpawn(MonsterType t, int dungeonLevel);
MonsterType pickMonster(int dungeonLevel);
void spawnMonsters(int dungeonLevel);
void moveEntity(Entity* entity, Position newPos);

extern Entity* player;
extern Entity* monsters[MAX_MONSTERS];
extern int monsterCount;