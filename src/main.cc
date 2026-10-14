#include "ctx.h"
#include "enemy.h"
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

    Painter painter;
    painter.drawMap();
    painter.drawEntities();

    g_ctx.running = true;
    while (g_ctx.running) {
        painter.clearScreen();
        painter.drawMap();
        painter.drawEntities();

        g_ctx.msg_area.display();
        g_ctx.msg_area.displayStats();

        int ch = getch();
        g_ctx.msg_area.clear();
        handleInput(ch);

        for (auto &e : g_ctx.entities)
            static_cast<Enemy &>(*e).follow(*g_ctx.entities[0]);
    }

    endwin();

    return EXIT_SUCCESS;
}