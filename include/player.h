#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "utils.h"

class Player : public Entity
{
public:
    int dungeon_level;
    int xp;
    int xp_level;
    int xp_goal;
    int potions;

    Player(int ch, Position pos, int hp, int strength);

    ~Player() override = default;

    void move(Direction direction) override;
    void takeDamage(int count, const Entity &attacker) override;
    void attack(Entity &target) override;

    void heal(this Player &self);
};

#endif // PLAYER_H