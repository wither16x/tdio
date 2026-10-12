#include "player.h"
#include <ncurses.h>

Player::Player(int ch, std::pair<int, int> pos)
    : ch(ch), pos(pos)
{}

void Player::draw(this const Player &self)
{
    mvaddch(self.pos.second, self.pos.first, self.ch);
}