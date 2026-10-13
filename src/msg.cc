#include "msg.h"
#include "ctx.h"
#include "win.h"
#include <ncurses.h>

void MessageArea::clear(this MessageArea &self)
{
    self.text.clear();
}

void MessageArea::display(this const MessageArea &self)
{
    mvprintw(WINDOW_HEIGHT + 1, 0, "%s", self.text.c_str());
}

void MessageArea::displayStats() const
{
    mvprintw(WINDOW_HEIGHT + 2, 0, "Dungeon level: %d", g_ctx.player.dungeon_level);
}