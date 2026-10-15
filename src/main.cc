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
        if (not handleInput(ch))
            continue;

        for (std::size_t i = 1; i < g_ctx.entities.size(); i++)
            static_cast<Enemy &>(*g_ctx.entities[i]).follow(*g_ctx.entities[0]);

        for (std::size_t i = 1; i < g_ctx.entities.size(); i++) {
            if (g_ctx.entities[i]->getHealth() <= 0) {
                g_ctx.entities.erase(
                    g_ctx.entities.begin() + static_cast<std::ptrdiff_t>(i)
                );
            }
        }
    }

    endwin();

    return EXIT_SUCCESS;
}