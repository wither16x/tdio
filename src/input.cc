#include "input.h"
#include "ctx.h"
#include "utils.h"
#include "map.h"
#include "player.h"

void handleInput(int ch)
{
    switch (ch) {
    case 'q':
        ctx.running = false;
        break;
    case 'h':
        player.move(Direction::West);
        break;
    case 'j':
        player.move(Direction::South);
        break;
    case 'k':
        player.move(Direction::North);
        break;
    case 'l':
        player.move(Direction::East);
        break;
    case '>':
        if (not player.isOnTile('>'))
            break;
        map.generate();
        player.teleport(map.findFreePos());
        break;
    }
}