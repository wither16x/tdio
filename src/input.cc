#include "input.h"
#include "ctx.h"
#include "utils.h"
#include "player.h"

bool handleInput(int ch)
{
    switch (ch) {
    case 'q':
        g_ctx.running = false;
        return false;
    case 'h':
        g_ctx.entities[0]->move(Direction::West);
        return true;
    case 'j':
        g_ctx.entities[0]->move(Direction::South);
        return true;
    case 'k':
        g_ctx.entities[0]->move(Direction::North);
        return true;
    case 'l':
        g_ctx.entities[0]->move(Direction::East);
        return true;
    case '>':
        if (not g_ctx.entities[0]->isOnTile('>')) {
            g_ctx.msg_area.set("There are no stairs here.");
            return false;
        }

        g_ctx.msg_area.set("You descend the stairs...");
        g_ctx.map.generate();
        g_ctx.entities[0]->setPos(g_ctx.map.findFreePos());
        ++static_cast<Player &>(*g_ctx.entities[0]).dungeon_level;
        return false;
    case 'd': {
        auto &player = static_cast<Player &>(*g_ctx.entities[0]);
        if (player.potions > 0) {
            --player.potions;
            player.heal();
        }
        return false;
    }
    default:
        return false;
    }

    return false;
}