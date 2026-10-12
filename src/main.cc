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

    Painter painter;
    Player player('@', {0, 0});

    painter.drawPlayer(player);

    bool running = true;
    while (running) {
        int ch = getch();
        if (ch == 'q')
            running = false;

        painter.drawPlayer(player);
    }

    endwin();

    return EXIT_SUCCESS;
}