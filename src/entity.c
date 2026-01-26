#include "entity.h"
#include "fov.h"
#include "position.h"
#include "map.h"
#include <stddef.h>

void moveEntity(Entity *entity, Position newPos) {
    if (!isInMap(newPos.y, newPos.x)) {
        return;
    }

    if (map[newPos.y][newPos.x].walkable) {
        map[entity->pos.y][entity->pos.x].monster = NULL;
        entity->pos.x = newPos.x;
        entity->pos.y = newPos.y;
        map[newPos.y][newPos.x].monster = entity;
    }
}