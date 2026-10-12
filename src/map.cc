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
            self.tiles[static_cast<std::size_t>(y * WINDOW_WIDTH + x)]
                = {'#', {x, y}};
    }

    // int nrooms = std::uniform_int_distribution<int> (MIN_ROOMS, MAX_ROOMS)(rng);
}

const std::array<Tile, WINDOW_WIDTH * WINDOW_HEIGHT> &Map::getTiles(this const Map &self)
{
    return self.tiles;
}

const Tile &Map::at(this const Map &self, std::pair<int, int> pos)
{
    return self.tiles.at(static_cast<std::size_t>(pos.second * WINDOW_WIDTH + pos.first));
}