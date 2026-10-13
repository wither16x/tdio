#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "utils.h"
#include <utility>

class Player : public Entity
{
public:
    int dungeon_level;

    Player(int ch, std::pair<int, int> pos);

    ~Player() override = default;

    void move(Direction direction) override;
};

#endif // PLAYER_H