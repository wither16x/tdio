#ifndef CTX_H
#define CTX_H

#include "map.h"
#include "msg.h"
#include "entity.h"
#include <memory>
#include <random>
#include <vector>

struct Context
{
    bool running;
    std::random_device randdev;
    MessageArea msg_area;
    Map map;
    // entities[0] is always the player
    std::vector<std::unique_ptr<Entity>> entities;
};

inline Context g_ctx;

#endif // CTX_H