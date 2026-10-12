#include "player.h"
#include <ncurses.h>
#include <cstdlib>

int main()
{
    initscr();
    curs_set(0);
    noecho();
    keypad(stdscr, true);

    Player player('@', {0, 0});
    player.draw();

    bool running = true;
    while (running) {
        int ch = getch();
        if (ch == 'q')
            running = false;

        player.draw();
    }

    endwin();

    return EXIT_SUCCESS;
}