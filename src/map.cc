#include "map.h"
#include "ctx.h"
#include "enemy.h"
#include "player.h"
#include "utils.h"
#include "win.h"
#include <algorithm>
#include <cstdlib>
#include <memory>
#include <random>
#include <array>
#include <ranges>
#include <utility>

Room::Room(Position pos, int w, int h)
    : pos(pos), center({pos.x + w / 2, pos.y + h / 2}), width(w), height(h)
{}

bool Room::overlaps(this const Room &self, const Room &other)
{
    return not (
        self.pos.x + self.width < other.pos.x
        or self.pos.y + self.height < other.pos.y
        or self.pos.x > other.pos.x + other.width
        or self.pos.y > other.pos.y + other.height
    );
}

void Map::generate(this Map &self)
{
    std::mt19937 rng(g_ctx.randdev());

    for (int y = 0; y < WINDOW_HEIGHT; y++) {
        for (int x = 0; x < WINDOW_WIDTH; x++)
            self.tiles.at(static_cast<std::size_t>(y * WINDOW_WIDTH + x))
                = {'#', false, false, {x, y}};
    }

    int nrooms = std::uniform_int_distribution(MIN_ROOMS, MAX_ROOMS)(rng);
    std::vector<Room> rooms;
    int attempts = 0;
    constexpr int MAX_ATTEMPTS = MAX_ROOMS * 10;

    while (static_cast<int>(rooms.size()) < nrooms and attempts++ < MAX_ATTEMPTS) {
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
        for (int y = r.pos.y; y < r.pos.y + r.height; y++) {
            for (int x = r.pos.x; x < r.pos.x + r.width; x++) {
                self.tiles.at(static_cast<std::size_t>(y * WINDOW_WIDTH + x))
                    = {'.', true, false, {x, y}};
            }
        }

        if (i > 0)
            self.connectRooms(rooms[static_cast<std::size_t>(i) - 1], r);
    }

    auto stair_pos = self.findFreePos();
    self.tiles[static_cast<std::size_t>(stair_pos.y * WINDOW_WIDTH + stair_pos.x)]
        = {'>', true, false, stair_pos};

    if (not g_ctx.entities.empty()) {
        auto &player = static_cast<Player &>(*g_ctx.entities[0]);
        g_ctx.entities.erase(g_ctx.entities.begin() + 1, g_ctx.entities.end());
        g_ctx.entities[0] = std::make_unique<Player>(player);
    } else {
        g_ctx.entities.push_back(
            std::make_unique<Player>('@', self.findFreePos(), 12, 2)
        );
    }

    int nenemies = std::uniform_int_distribution(MIN_ENEMIES, MAX_ENEMIES)(rng);
    attempts = 0;
    constexpr int MAX_ATTEMPTS_ENEMIES = MAX_ENEMIES * 10;

    while (static_cast<int>(g_ctx.entities.size() + 1) < nenemies and attempts++ < MAX_ATTEMPTS_ENEMIES) {
        std::vector<Position> positions;

        for (int y = 0; y < WINDOW_HEIGHT; y++) {
            for (int x = 0; x < WINDOW_WIDTH; x++) {
                if (self.at({x, y}).walkable)
                    positions.emplace_back(x, y);
            }
        }

        std::size_t idx = std::uniform_int_distribution<std::size_t>
            (0, positions.size() - 1)(rng);
        auto kind = static_cast<EnemyKind>(std::uniform_int_distribution
            (0, std::to_underlying(EnemyKind::LastEnemy) - 1)(rng));

        auto e = new Enemy(kind, positions[idx]);

        int dungeon_lv = static_cast<const Player &>(*g_ctx.entities[0]).dungeon_level;
        if (dungeon_lv >= e->dungeon_level_min and dungeon_lv <= e->dungeon_level_max)
            g_ctx.entities.push_back(std::make_unique<Enemy>(*e));
    }
}

void Map::connectRooms(this Map &self, const Room &r1, const Room &r2)
{
    auto [x, y] = r1.center;
    const auto [tx, ty] = r2.center;

    while (x != tx or y != ty) {
        if (x != tx)
            x += (tx > x) ? 1 : -1;
        else
            y += (ty > y) ? 1 : -1;

        self.tiles.at(static_cast<std::size_t>(y * WINDOW_WIDTH + x))
            = {'.', true, false, {x, y}};
    }
}

const std::array<Tile, WINDOW_WIDTH * WINDOW_HEIGHT> &Map::getTiles(this const Map &self)
{
    return self.tiles;
}

const Tile &Map::at(this const Map &self, Position pos)
{
    return self.tiles.at(static_cast<std::size_t>(pos.y * WINDOW_WIDTH + pos.x));
}

Tile &Map::at(this Map &self, Position pos)
{
    return self.tiles.at(static_cast<std::size_t>(pos.y * WINDOW_WIDTH + pos.x));
}

Position Map::findFreePos(this const Map &self)
{
    std::vector<Position> positions;

    for (int y = 0; y < WINDOW_HEIGHT; y++) {
        for (int x = 0; x < WINDOW_WIDTH; x++) {
            if (self.at({x, y}).walkable)
                positions.emplace_back(x, y);
        }
    }

    std::mt19937 rng(g_ctx.randdev());
    std::size_t idx = std::uniform_int_distribution<std::size_t>
        (0, positions.size() - 1)(rng);

    return positions[idx];
}