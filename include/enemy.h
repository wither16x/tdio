#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"
#include "utils.h"
#include <utility>

class Enemy : public Entity
{
public:
    Enemy(int ch, std::pair<int, int> pos);

    ~Enemy() override = default;

    void move(Direction direction) override;
};

#endif // ENEMY_H