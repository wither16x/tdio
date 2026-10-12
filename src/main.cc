#include "test.h"
#include <ncurses.h>

int main()
{
    initscr();
    curs_set(0);
    noecho();
    keypad(stdscr, true);

    print("hello");
    getch();

    endwin();

    return 0;
}