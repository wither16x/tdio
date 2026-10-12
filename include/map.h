#ifndef MAP_H
#define MAP_H

#include "win.h"
#include <utility>
#include <array>

struct Tile
{
    int ch;
    std::pair<int, int> pos;
};

struct Room
{
    std::pair<int, int> pos;
    int width;
    int height;

    bool overlaps(this const Room &self, const Room &other);
};

class Map
{
    static constexpr int MIN_ROOMS = 4;
    static constexpr int MAX_ROOMS = 12;
    static constexpr int MIN_ROOM_SIDE_WIDTH = 3;
    static constexpr int MAX_ROOM_SIDE_WIDTH = 15;

    std::array<Tile, WINDOW_WIDTH * WINDOW_HEIGHT> tiles;

public:
    void generate(this Map &self);

    const std::array<Tile, WINDOW_WIDTH * WINDOW_HEIGHT> &getTiles(this const Map &self);
    const Tile &at(this const Map &self, std::pair<int, int> pos);
};

inline Map map;

#endif // MAP_H