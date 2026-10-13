#include "player.h"
#include "utils.h"
#include <ncurses.h>

Player::Player(int ch, std::pair<int, int> pos)
    : Entity(ch, pos), dungeon_level(1)
{}

void Player::move(Direction direction)
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