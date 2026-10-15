#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "utils.h"
#include <utility>

class Player : public Entity
{
public:
    int dungeon_level;
    int xp;
    int xp_level;
    int xp_goal;
    int potions;

    Player(int ch, std::pair<int, int> pos, int hp, int strength);

    ~Player() override = default;

    void move(Direction direction) override;
    void takeDamage(int count, const Entity &attacker) override;

    void attack(this Player &self, Entity &target);
    void heal(this Player &self);
};

#endif // PLAYER_H