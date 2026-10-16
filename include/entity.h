#ifndef ENTITY_H
#define ENTITY_H

#include "utils.h"
#include <string>

class Entity
{
protected:
    std::string name;
    int ch;
    Position pos;
    int hp;
    int max_hp;
    int strength;

public:
    Entity(int ch, Position pos);

    virtual ~Entity() = default;

    int getChar(this const Entity &self);
    Position getPos(this const Entity &self);
    int getHealth(this const Entity &self);
    int getMaxHealth(this const Entity &self);
    const std::string &getName(this const Entity &self);

    void setPos(this Entity &self, Position pos);
    bool isOnTile(this const Entity &self, int tilech);

    virtual void move(Direction direction) = 0;
    virtual void takeDamage(int count, const Entity &attacker) = 0;
    virtual void attack(Entity &target) = 0;
};

#endif // ENTITY_H