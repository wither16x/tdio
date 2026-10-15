#include "msg.h"
#include "ctx.h"
#include "win.h"
#include "player.h"
#include <ncurses.h>

void MessageArea::clear(this MessageArea &self)
{
    self.lines.clear();
}

void MessageArea::display(this const MessageArea &self)
{
    int row = 2;
    for (const auto &ln : self.lines)
        mvprintw(WINDOW_HEIGHT + row++, 0, "%s", ln.c_str());
}

void MessageArea::displayStats() const
{
    auto &player = static_cast<const Player &>(*g_ctx.entities[0]);

    mvprintw(WINDOW_HEIGHT + 1, 0, "HP: %d, Dungeon level: %d",
        player.getHealth(),
        player.dungeon_level
    );
}