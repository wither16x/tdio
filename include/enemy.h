#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"
#include "utils.h"
#include <utility>

enum class EnemyKind
{
    Bat,
    Zombie,
    Snake,
    Goblin,
    Wolf,

    LastEnemy
};

class Enemy : public Entity
{
    EnemyKind kind;

public:
    int dungeon_level_min;
    // set to very high value like std::numeric_limits<int>::max() for no max level
    int dungeon_level_max;

    Enemy(EnemyKind kind, std::pair<int, int> pos);

    ~Enemy() override = default;

    void move(Direction direction) override;
};

#endif // ENEMY_H