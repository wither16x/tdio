#include "enemy.h"
#include <limits>

Enemy::Enemy(EnemyKind kind, std::pair<int, int> pos)
    : Entity(' ', pos), kind(kind)
{
    switch (this->kind) {
    case EnemyKind::Bat:
        this->ch = 'B';
        this->dungeon_level_min = 1;
        this->dungeon_level_max = std::numeric_limits<int>::max();
        break;
    case EnemyKind::Zombie:
        this->ch = 'Z';
        this->dungeon_level_min = 1;
        this->dungeon_level_max = std::numeric_limits<int>::max();
        break;
    case EnemyKind::Snake:
        this->ch = 'S';
        this->dungeon_level_min = 2;
        this->dungeon_level_max = std::numeric_limits<int>::max();
        break;
    case EnemyKind::Goblin:
        this->ch = 'G';
        this->dungeon_level_min = 4;
        this->dungeon_level_max = std::numeric_limits<int>::max();
        break;
    case EnemyKind::Wolf:
        this->ch = 'W';
        this->dungeon_level_min = 5;
        this->dungeon_level_max = std::numeric_limits<int>::max();
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