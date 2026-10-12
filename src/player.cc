#include "player.h"
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