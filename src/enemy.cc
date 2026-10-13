#include "enemy.h"

Enemy::Enemy(EnemyKind kind, std::pair<int, int> pos)
    : Entity(' ', pos), kind(kind)
{
    switch (this->kind) {
    case EnemyKind::Bat:
        this->ch = 'B';
        break;
    case EnemyKind::Zombie:
        this->ch = 'Z';
        break;
    case EnemyKind::Snake:
        this->ch = 'S';
        break;
    case EnemyKind::Goblin:
        this->ch = 'G';
        break;
    case EnemyKind::Wolf:
        this->ch = 'W';
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