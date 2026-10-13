#include "input.h"
#include "ctx.h"
#include "utils.h"
#include "player.h"

void handleInput(int ch)
{
    switch (ch) {
    case 'q':
        g_ctx.running = false;
        break;
    case 'h':
        g_ctx.entities[0]->move(Direction::West);
        break;
    case 'j':
        g_ctx.entities[0]->move(Direction::South);
        break;
    case 'k':
        g_ctx.entities[0]->move(Direction::North);
        break;
    case 'l':
        g_ctx.entities[0]->move(Direction::East);
        break;
    case '>':
        if (not g_ctx.entities[0]->isOnTile('>')) {
            g_ctx.msg_area.set("There are no stairs here.");
            break;
        }

        g_ctx.msg_area.set("You descend the stairs...");
        g_ctx.map.generate();
        g_ctx.entities[0]->setPos(g_ctx.map.findFreePos());
        ++static_cast<Player &>(*g_ctx.entities[0]).dungeon_level;
        break;
    }
}