#include "enemy.h"
#include "ctx.h"
#include "utils.h"
#include <limits>
#include <cmath>

Enemy::Enemy(EnemyKind kind, std::pair<int, int> pos)
    : Entity(' ', pos), kind(kind)
{
    switch (this->kind) {
    case EnemyKind::Bat:
        this->ch = 'B';
        this->name = "Bat";
        this->hp = 3;
        this->strength = 1;
        this->dungeon_level_min = 1;
        this->dungeon_level_max = std::numeric_limits<int>::max();
        this->fov = 2;
        break;
    case EnemyKind::Zombie:
        this->ch = 'Z';
        this->name = "Zombie";
        this->hp = 8;
        this->strength = 2;
        this->dungeon_level_min = 1;
        this->dungeon_level_max = std::numeric_limits<int>::max();
        this->fov = 3;
        break;
    case EnemyKind::Snake:
        this->ch = 'S';
        this->name = "Snake";
        this->hp = 4;
        this->strength = 1;
        this->dungeon_level_min = 2;
        this->dungeon_level_max = std::numeric_limits<int>::max();
        this->fov = 2;
        break;
    case EnemyKind::Goblin:
        this->ch = 'G';
        this->name = "Goblin";
        this->hp = 12;
        this->strength = 3;
        this->dungeon_level_min = 4;
        this->dungeon_level_max = std::numeric_limits<int>::max();
        this->fov = 4;
        break;
    case EnemyKind::Wolf:
        this->ch = 'W';
        this->name = "Wolf";
        this->hp = 10;
        this->strength = 3;
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

void Enemy::takeDamage(int count, const Entity &attacker)
{
    g_ctx.msg_area.set("{} hits the {}.", attacker.getName(), this->name);
    this->hp -= count;

    if (this->hp <= 0)
        g_ctx.msg_area.set("{} killed the {}!", attacker.getName(), this->name);
}

void Enemy::follow(this Enemy &self, Entity &target)
{
    if (not self.sees(target))
        return;

    const auto [tx, ty] = target.getPos();
    const auto [ex, ey] = self.getPos();
    const int dx = tx - ex;
    const int dy = ty - ey;

    if (std::abs(dx) + std::abs(dy) < 2) {
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

void Enemy::attack(this const Enemy &self, Entity &target)
{
    if (self.hp <= 0)
        return;
    target.takeDamage(self.strength, self);
}

bool Enemy::sees(this const Enemy &self, const Entity &target)
{
    return getDistance(self.getPos(), target.getPos()) < self.fov;
}