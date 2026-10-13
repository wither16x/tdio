#ifndef CTX_H
#define CTX_H

#include <random>

struct Context
{
    bool running;
    std::random_device randdev;
};

inline Context g_ctx;

#endif // CTX_H