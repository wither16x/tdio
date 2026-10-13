#include "utils.h"
#include <cmath>

int getDistance(std::pair<int, int> origin, std::pair<int, int> target)
{
    double dx = origin.first - target.first;
    double dy = origin.second - target.second;
    int distance = static_cast<int>(std::floor(std::sqrt((dx * dx) + (dy * dy))));

    return distance;
}