#include "ctx.h"
#include "input.h"
#include "map.h"
#include "msg.h"
#include "painter.h"
#include "player.h"
#include <ncurses.h>
#include <cstdlib>

int main()
{
    initscr();
    curs_set(0);
    noecho();
    keypad(stdscr, true);

    map.generate();
    player.teleport(map.findFreePos());

    Painter painter;
    painter.drawMap();
    painter.drawPlayer();

    ctx.running = true;
    while (ctx.running) {
        painter.clearScreen();
        painter.drawMap();
        painter.drawPlayer();

        msg_area.display();

        int ch = getch();
        msg_area.clear();
        handleInput(ch);
    }

    endwin();

    return EXIT_SUCCESS;
}