#include "painter.h"
#include <ncurses.h>

void Painter::drawPlayer(const Player &player)
{
    mvaddch(player.getPos().second, player.getPos().first, player.getChar());
}