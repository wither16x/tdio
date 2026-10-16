#ifndef UTILS_H
#define UTILS_H

#include <cmath>

enum class Direction
{
    North,
    South,
    East,
    West
};

enum class FightAction
{
    Hit,
    Miss,

    FightActionCount
};

struct Position
{
    int x;
    int y;

    constexpr int distance(this const Position &self, const Position &target)
    {
        double dx = self.x - target.x;
        double dy = self.y - target.y;
        int distance = static_cast<int>(std::floor(std::sqrt((dx * dx) + (dy * dy))));

        return distance;
    }

    inline constexpr bool operator ==(this const Position &self, const Position &other)
    {
        return self.x == other.x and self.y == other.y;
    }
};

#endif // UTILS_H