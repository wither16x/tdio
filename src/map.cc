#include "map.h"
#include "ctx.h"
#include "win.h"
#include <random>
#include <array>

void Map::generate(this Map &self)
{
    std::mt19937 rng(ctx.randdev());

    for (int y = 0; y < WINDOW_HEIGHT; y++) {
        for (int x = 0; x < WINDOW_WIDTH; x++)
            self.tiles.at(static_cast<std::size_t>(y * WINDOW_WIDTH + x))
                = {'#', {x, y}};
    }

    int nrooms = std::uniform_int_distribution(MIN_ROOMS, MAX_ROOMS)(rng);
    std::vector<Room> rooms;

    for (int i = 0; i < nrooms; i++) {
        int room_w = std::uniform_int_distribution
            (MIN_ROOM_SIDE_WIDTH, MAX_ROOM_SIDE_WIDTH)(rng);
        int room_h = std::uniform_int_distribution
            (MIN_ROOM_SIDE_WIDTH, MAX_ROOM_SIDE_WIDTH)(rng);
        int room_x = std::uniform_int_distribution(1, WINDOW_WIDTH - room_w - 1)(rng);
        int room_y = std::uniform_int_distribution(1, WINDOW_HEIGHT - room_h - 1)(rng);

        rooms.push_back({{room_x, room_y}, room_w, room_h});
    }

    for (auto &r : rooms) {
        for (int y = r.pos.second; y < r.pos.second + r.height; y++) {
            for (int x = r.pos.first; x < r.pos.first + r.width; x++)
                self.tiles.at(static_cast<std::size_t>(y * WINDOW_WIDTH + x))
                    = {'.', {x, y}};
        }
    }
}

const std::array<Tile, WINDOW_WIDTH * WINDOW_HEIGHT> &Map::getTiles(this const Map &self)
{
    return self.tiles;
}

const Tile &Map::at(this const Map &self, std::pair<int, int> pos)
{
    return self.tiles.at(static_cast<std::size_t>(pos.second * WINDOW_WIDTH + pos.first));
}