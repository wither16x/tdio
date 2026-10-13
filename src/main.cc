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

    g_map.generate();
    g_player.teleport(g_map.findFreePos());

    Painter painter;
    painter.drawMap();
    painter.drawPlayer();

    g_ctx.running = true;
    while (g_ctx.running) {
        painter.clearScreen();
        painter.drawMap();
        painter.drawPlayer();

        g_msg_area.display();
        g_msg_area.displayStats();

        int ch = getch();
        g_msg_area.clear();
        handleInput(ch);
    }

    endwin();

    return EXIT_SUCCESS;
}