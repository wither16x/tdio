#include "input.h"
#include "ctx.h"
#include "utils.h"

void handleInput(int ch)
{
    switch (ch) {
    case 'q':
        g_ctx.running = false;
        break;
    case 'h':
        g_ctx.player.move(Direction::West);
        break;
    case 'j':
        g_ctx.player.move(Direction::South);
        break;
    case 'k':
        g_ctx.player.move(Direction::North);
        break;
    case 'l':
        g_ctx.player.move(Direction::East);
        break;
    case '>':
        if (not g_ctx.player.isOnTile('>')) {
            g_ctx.msg_area.set("There are no stairs here.");
            break;
        }

        g_ctx.msg_area.set("You descend the stairs...");
        g_ctx.map.generate();
        g_ctx.player.setPos(g_ctx.map.findFreePos());
        ++g_ctx.player.dungeon_level;
        break;
    }
}