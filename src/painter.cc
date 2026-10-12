#include "painter.h"
#include "map.h"
#include "player.h"
#include "win.h"
#include <ncurses.h>

void Painter::drawPlayer()
{
    mvaddch(player.getPos().second, player.getPos().first, player.getChar());
}

void Painter::drawMap()
{
    for (int y = 0; y < WINDOW_HEIGHT; y++) {
        for (int x = 0; x < WINDOW_WIDTH; x++) {
            const Tile &t = map.at({x, y});
            mvaddch(t.pos.second, t.pos.first, t.ch);
        }
    }
}

void Painter::clearScreen()
{
    clear();
}