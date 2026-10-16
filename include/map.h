#ifndef MAP_H
#define MAP_H

#include "utils.h"
#include "win.h"
#include <array>
#include <vector>

struct Tile
{
    int ch;
    bool walkable;
    bool seen;
    Position pos;
};

struct Room
{
    Position pos;
    Position center;
    int width;
    int height;

    Room(Position pos, int w, int h);

    bool overlaps(this const Room &self, const Room &other);
};

class Map
{
    static constexpr int MIN_ROOMS = 4;
    static constexpr int MAX_ROOMS = 12;
    static constexpr int MIN_ROOM_SIDE_WIDTH = 3;
    static constexpr int MAX_ROOM_SIDE_WIDTH = 15;
    static constexpr int MIN_ENEMIES = 5;
    static constexpr int MAX_ENEMIES = 20;

    std::array<Tile, WINDOW_WIDTH * WINDOW_HEIGHT> tiles;
    std::vector<Room> rooms;

    void fillWithWalls(this Map &self);
    void carveRooms(this Map &self);
    void carvePaths(this Map &self);
    void generateStairs(this Map &self);
    void generateEntities(this Map &self);

public:
    void generate(this Map &self);
    void connectRooms(this Map &self, const Room &r1, const Room &r2);

    const std::array<Tile, WINDOW_WIDTH * WINDOW_HEIGHT> &getTiles(this const Map &self);
    const Tile &at(this const Map &self, Position pos);
    Tile &at(this Map &self, Position pos);
    Position findFreePos(this const Map &self);
};

#endif // MAP_H