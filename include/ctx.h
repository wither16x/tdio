#ifndef CTX_H
#define CTX_H

#include "map.h"
#include "msg.h"
#include "player.h"
#include <random>

struct Context
{
    bool running;
    std::random_device randdev;
    MessageArea msg_area;
    Map map;
    Player player{'@', {0, 0}};
};

inline Context g_ctx;

#endif // CTX_H