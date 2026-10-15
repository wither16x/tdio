#include "utils.h"
#include <cmath>

int getDistance(Position origin, Position target)
{
    double dx = origin.x - target.x;
    double dy = origin.y - target.y;
    int distance = static_cast<int>(std::floor(std::sqrt((dx * dx) + (dy * dy))));

    return distance;
}