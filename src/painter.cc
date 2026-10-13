#include "painter.h"
#include "ctx.h"
#include "utils.h"
#include "win.h"
#include <cmath>
#include <ncurses.h>

void Painter::drawEntities()
{
    int px = g_ctx.entities[0]->getPos().first;
    int py = g_ctx.entities[0]->getPos().second;
    int fov_radius = 5;

    for (const auto &e : g_ctx.entities) {
        for (int y = py - fov_radius; y < py + fov_radius; y++) {
            for (int x = px - fov_radius; x < px + fov_radius; x++) {
                if (x >= 0 and x < WINDOW_WIDTH and y >= 0 and y < WINDOW_HEIGHT) {
                    int distance = getDistance(g_ctx.entities[0]->getPos(), e->getPos());
                    if (distance < fov_radius)
                        mvaddch(e->getPos().second, e->getPos().first, e->getChar());
                }
            }
        }
    }
}

void Painter::drawMap()
{
    int px = g_ctx.entities[0]->getPos().first;
    int py = g_ctx.entities[0]->getPos().second;
    int fov_radius = 5;

    for (int y = 0; y < WINDOW_HEIGHT; y++) {
        for (int x = 0; x < WINDOW_WIDTH; x++) {
            const Tile &t = g_ctx.map.at({x, y});
            if (t.seen)
                mvaddch(t.pos.second, t.pos.first, t.ch);
        }
    }

    for (int y = py - fov_radius; y < py + fov_radius; y++) {
        for (int x = px - fov_radius; x < px + fov_radius; x++) {
            if (x >= 0 and x < WINDOW_WIDTH and y >= 0 and y < WINDOW_HEIGHT) {
                int distance = getDistance(g_ctx.entities[0]->getPos(), {x, y});
                if (distance < fov_radius) {
                    Tile &t = g_ctx.map.at({x, y});
                    mvaddch(t.pos.second, t.pos.first, t.ch);
                    if (not t.seen)
                        t.seen = true;
                }
            }
        }
    }
}

void Painter::clearScreen()
{
    clear();
}