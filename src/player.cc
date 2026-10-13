#include "player.h"
#include "utils.h"
#include "map.h"
#include "win.h"
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
    auto new_pos = self.pos;

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

    self.teleport(new_pos);
}

void Player::teleport(this Player &self, std::pair<int, int> new_pos)
{
    if (new_pos.first >= 0 and new_pos.first < WINDOW_WIDTH
    and new_pos.second >= 0 and new_pos.second < WINDOW_HEIGHT
    and map.at(new_pos).walkable)
        self.pos = new_pos;
}

bool Player::isOnTile(this const Player &self, int tilech)
{
    return map.at(self.pos).ch == tilech;
}