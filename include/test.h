#ifndef TEST_H
#define TEST_H

#include <ncurses.h>

inline void print(const char *msg)
{
    mvwprintw(stdscr, 0, 0, "%s", msg);
}

#endif /* TEST_H */