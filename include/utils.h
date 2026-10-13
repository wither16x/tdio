#ifndef DIRECTION_H
#define DIRECTION_H

#include <utility>

enum class Direction
{
    North,
    South,
    East,
    West
};

int getDistance(std::pair<int, int> origin, std::pair<int, int> target);

#endif // DIRECTION_H