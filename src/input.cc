#include "input.h"
#include "ctx.h"
#include "msg.h"
#include "utils.h"
#include "map.h"
#include "player.h"

void handleInput(int ch)
{
    switch (ch) {
    case 'q':
        g_ctx.running = false;
        break;
    case 'h':
        g_player.move(Direction::West);
        break;
    case 'j':
        g_player.move(Direction::South);
        break;
    case 'k':
        g_player.move(Direction::North);
        break;
    case 'l':
        g_player.move(Direction::East);
        break;
    case '>':
        if (not g_player.isOnTile('>')) {
            g_msg_area.set("There are no stairs here.");
            break;
        }

        g_msg_area.set("You descend the stairs...");
        g_map.generate();
        g_player.teleport(g_map.findFreePos());
        ++g_player.dungeon_level;
        break;
    }
}