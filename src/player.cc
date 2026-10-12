#include "player.h"
#include "direction.h"
#include <ncurses.h>

Player::Player(int ch, std::pair<int, int> pos)
    : ch(ch), pos(pos)
{}

int Player::getChar(this const Player &self)
{
    return self.ch;
}

std::pair<int, int> Player::getPos(this const Player &self)
{
    return self.pos;
}

void Player::move(this Player &self, Direction direction)
{
    switch (direction) {
    case Direction::North:
        --self.pos.second;
        break;
    case Direction::South:
        ++self.pos.second;
        break;
    case Direction::East:
        ++self.pos.first;
        break;
    case Direction::West:
        --self.pos.first;
        break;
    }
}