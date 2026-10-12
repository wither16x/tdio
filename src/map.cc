#include "map.h"
#include "ctx.h"
#include "win.h"
#include <algorithm>
#include <cstdlib>
#include <random>
#include <array>
#include <ranges>

Room::Room(std::pair<int, int> pos, int w, int h)
    : pos(pos), center({pos.first / 2, pos.second / 2}), width(w), height(h)
{}

bool Room::overlaps(this const Room &self, const Room &other)
{
    return not (
        self.pos.first + self.width < other.pos.first
        or self.pos.second + self.height < other.pos.second
        or self.pos.first > other.pos.first + other.width
        or self.pos.second > other.pos.second + other.height
    );
}

void Map::generate(this Map &self)
{
    std::mt19937 rng(ctx.randdev());

    for (int y = 0; y < WINDOW_HEIGHT; y++) {
        for (int x = 0; x < WINDOW_WIDTH; x++)
            self.tiles.at(static_cast<std::size_t>(y * WINDOW_WIDTH + x))
                = {'#', false, {x, y}};
    }

    int nrooms = std::uniform_int_distribution(MIN_ROOMS, MAX_ROOMS)(rng);
    std::vector<Room> rooms;
    int attmp_posts = 0;
    constexpr int MAX_ATtmp_posTS = MAX_ROOMS * 2;

    while (static_cast<int>(rooms.size()) < nrooms and attmp_posts++ < MAX_ATtmp_posTS) {
        int room_w = std::uniform_int_distribution
            (MIN_ROOM_SIDE_WIDTH, MAX_ROOM_SIDE_WIDTH)(rng);
        int room_h = std::uniform_int_distribution
            (MIN_ROOM_SIDE_WIDTH, MAX_ROOM_SIDE_WIDTH)(rng);
        int room_x = std::uniform_int_distribution(1, WINDOW_WIDTH - room_w - 1)(rng);
        int room_y = std::uniform_int_distribution(1, WINDOW_HEIGHT - room_h - 1)(rng);

        Room r({room_x, room_y}, room_w, room_h);

        bool collides = std::ranges::any_of(rooms, [&](const Room &other) {
            return r.overlaps(other);
        });
        if (collides)
            continue;

        rooms.push_back(r);
    }

    for (auto [i, r] : std::ranges::views::enumerate(rooms)) {
        for (int y = r.pos.second; y < r.pos.second + r.height; y++) {
            for (int x = r.pos.first; x < r.pos.first + r.width; x++) {
                self.tiles.at(static_cast<std::size_t>(y * WINDOW_WIDTH + x))
                    = {'.', true, {x, y}};

                if (i > 0)
                    self.connectRooms(rooms[static_cast<std::size_t>(i) - 1], r);
            }
        }
    }
}


void Map::connectRooms(this Map &self, const Room &r1, const Room &r2)
{
    std::pair<int, int> tmp_pos = r1.center;
    bool connected = false;

    while (not connected) {
        if (std::abs((tmp_pos.first - 1) - r2.pos.first) < std::abs(tmp_pos.first - r2.pos.first))
            --tmp_pos.first;
        else if (std::abs((tmp_pos.first + 1) - r2.pos.first) < std::abs(tmp_pos.first - r2.pos.first))
            ++tmp_pos.first;
        else if (std::abs((tmp_pos.second + 1) - r2.pos.second) < std::abs(tmp_pos.second - r2.pos.second))
            ++tmp_pos.second;
        else if (std::abs((tmp_pos.second - 1) - r2.pos.second) < std::abs(tmp_pos.second - r2.pos.second))
            --tmp_pos.second;
        else
            connected = true;

        self.tiles.at(static_cast<std::size_t>(tmp_pos.second * WINDOW_WIDTH + tmp_pos.first))
            = {'.', true, tmp_pos};
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

std::pair<int, int> Map::findFreePos(this const Map &self)
{
    std::vector<std::pair<int, int>> positions;

    for (int y = 0; y < WINDOW_HEIGHT; y++) {
        for (int x = 0; x < WINDOW_WIDTH; x++) {
            if (self.at({x, y}).walkable)
                positions.emplace_back(x, y);
        }
    }

    std::mt19937 rng(ctx.randdev());
    std::size_t idx = std::uniform_int_distribution<std::size_t>
        (0, positions.size())(rng);

    return positions[idx];
}