#include "entity.h"
#include "win.h"
#include "ctx.h"

Entity::Entity(int ch, std::pair<int, int> pos)
    : ch(ch), pos(pos), attacked(false)
{}

int Entity::getChar(this const Entity &self)
{
    return self.ch;
}

std::pair<int, int> Entity::getPos(this const Entity &self)
{
    return self.pos;
}

void Entity::setPos(this Entity &self, std::pair<int, int> new_pos)
{
    if (new_pos.first >= 0 and new_pos.first < WINDOW_WIDTH
    and new_pos.second >= 0 and new_pos.second < WINDOW_HEIGHT
    and g_ctx.map.at(new_pos).walkable)
        self.pos = new_pos;
}

bool Entity::isOnTile(this const Entity &self, int tilech)
{
    return g_ctx.map.at(self.pos).ch == tilech;
}