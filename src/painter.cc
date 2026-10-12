#include "painter.h"
#include "player.h"
#include <ncurses.h>

void Painter::drawPlayer()
{
    mvaddch(player.getPos().second, player.getPos().first, player.getChar());
}

void Painter::clearScreen()
{
    clear();
}