#include "enemy.h"
#include "utils.h"
#include <limits>
#include <cmath>

Enemy::Enemy(EnemyKind kind, std::pair<int, int> pos)
    : Entity(' ', pos), kind(kind)
{
    switch (this->kind) {
    case EnemyKind::Bat:
        this->ch = 'B';
        this->dungeon_level_min = 1;
        this->dungeon_level_max = std::numeric_limits<int>::max();
        this->fov = 2;
        break;
    case EnemyKind::Zombie:
        this->ch = 'Z';
        this->dungeon_level_min = 1;
        this->dungeon_level_max = std::numeric_limits<int>::max();
        this->fov = 3;
        break;
    case EnemyKind::Snake:
        this->ch = 'S';
        this->dungeon_level_min = 2;
        this->dungeon_level_max = std::numeric_limits<int>::max();
        this->fov = 2;
        break;
    case EnemyKind::Goblin:
        this->ch = 'G';
        this->dungeon_level_min = 4;
        this->dungeon_level_max = std::numeric_limits<int>::max();
        this->fov = 4;
        break;
    case EnemyKind::Wolf:
        this->ch = 'W';
        this->dungeon_level_min = 5;
        this->dungeon_level_max = std::numeric_limits<int>::max();
        this->fov = 4;
        break;
    default:
        break;
    }
}

void Enemy::move(Direction direction)
{
    auto new_pos = this->pos;

    switch (direction) {
    case Direction::North:
        --new_pos.second;
        break;
    case Direction::South:
        ++new_pos.second;
        break;
    case Direction::East:
        ++new_pos.first;
        break;
    case Direction::West:
        --new_pos.first;
        break;
    }

    this->setPos(new_pos);
}

void Enemy::follow(this Enemy &self, const Entity &target)
{
    if (not self.sees(target))
        return;

    const auto [tx, ty] = target.getPos();
    const auto dx = static_cast<long>(tx) - static_cast<long>(self.pos.first);
    const auto dy = static_cast<long>(ty) - static_cast<long>(self.pos.second);

    if (std::abs(dx) + std::abs(dy) <= 1) {
        self.attack(target);
        return;
    }

    if (dx > 0)
        self.move(Direction::East);
    else if (dx < 0)
        self.move(Direction::West);
    else if (dy > 0)
        self.move(Direction::South);
    else
        self.move(Direction::North);
}

void Enemy::attack(this const Enemy &self, const Entity &target)
{
    static_cast<void>(self);
    static_cast<void>(target);
    // TODO
}

bool Enemy::sees(this const Enemy &self, const Entity &target)
{
    return getDistance(self.getPos(), target.getPos()) < self.fov;
}