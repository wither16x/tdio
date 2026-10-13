#include "ctx.h"
#include "input.h"
#include "painter.h"
#include <ncurses.h>
#include <cstdlib>

int main()
{
    initscr();
    curs_set(0);
    noecho();
    keypad(stdscr, true);

    g_ctx.map.generate();
    g_ctx.player.setPos(g_ctx.map.findFreePos());

    Painter painter;
    painter.drawMap();
    painter.drawPlayer();

    g_ctx.running = true;
    while (g_ctx.running) {
        painter.clearScreen();
        painter.drawMap();
        painter.drawPlayer();

        g_ctx.msg_area.display();
        g_ctx.msg_area.displayStats();

        int ch = getch();
        g_ctx.msg_area.clear();
        handleInput(ch);
    }

    endwin();

    return EXIT_SUCCESS;
}