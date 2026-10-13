#ifndef ENTITY_H
#define ENTITY_H

#include "utils.h"
#include <utility>

class Entity
{
protected:
    int ch;
    std::pair<int, int> pos;

public:
    Entity(int ch, std::pair<int, int> pos);

    virtual ~Entity() = default;

    int getChar(this const Entity &self);
    std::pair<int, int> getPos(this const Entity &self);

    void setPos(this Entity &self, std::pair<int, int> pos);

    bool isOnTile(this const Entity &self, int tilech);

    virtual void move(Direction direction) = 0;
};

#endif // ENTITY_H