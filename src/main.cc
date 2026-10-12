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

    Painter painter;
    painter.drawPlayer();

    ctx.running = true;
    while (ctx.running) {
        int ch = getch();
        handleInput(ch);

        painter.drawPlayer();
    }

    endwin();

    return EXIT_SUCCESS;
}