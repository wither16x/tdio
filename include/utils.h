#ifndef UTILS_H
#define UTILS_H

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

    inline constexpr bool operator ==(this const Position &self, const Position &other)
    {
        return self.x == other.x and self.y == other.y;
    }
};

int getDistance(Position origin, Position target);

#endif // UTILS_H