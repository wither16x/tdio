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
    Enemy(EnemyKind kind, std::pair<int, int> pos);

    ~Enemy() override = default;

    void move(Direction direction) override;
};

#endif // ENEMY_H