#include "entity.h"
#include "utils.h"
#include "win.h"
#include "ctx.h"

Entity::Entity(int ch, Position pos)
    : ch(ch), pos(pos), hp(0), strength(0)
{}

int Entity::getChar(this const Entity &self)
{
    return self.ch;
}

Position Entity::getPos(this const Entity &self)
{
    return self.pos;
}

int Entity::getHealth(this const Entity &self)
{
    return self.hp;
}

int Entity::getMaxHealth(this const Entity &self)
{
    return self.max_hp;
}

const std::string &Entity::getName(this const Entity &self)
{
    return self.name;
}

void Entity::setPos(this Entity &self, Position new_pos)
{
    if (new_pos.x >= 0 and new_pos.x < WINDOW_WIDTH
    and new_pos.y >= 0 and new_pos.y < WINDOW_HEIGHT
    and g_ctx.map.at(new_pos).walkable)
        self.pos = new_pos;
}

bool Entity::isOnTile(this const Entity &self, int tilech)
{
    return g_ctx.map.at(self.pos).ch == tilech;
}