#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include "entity.h"
#include "position.h"
#include "fov.h"
#include "map.h"

void makeFOV(Entity* player) {
    int y, x, d;
    int RADIUS = 5;
    Position target;

    map[player->pos.y][player->pos.x].visible = true;
    map[player->pos.y][player->pos.x].seen = true;

    for (y = player->pos.y - RADIUS; y < player->pos.y + RADIUS; y++) {
        for (x = player->pos.x - RADIUS; x < player->pos.x + RADIUS; x++) {
            target.y = y;
            target.x = x;
            d = getDistance(player->pos, target);

            if (d < RADIUS) {
                if (isInMap(y, x) && lineOfSight(player->pos, target)) {
                    if (map[y][x].monster != NULL) {
                        map[y][x].monster->monsterInfo->visible = true;
                    }
                    map[y][x].visible = true;
                    map[y][x].seen = true;
                }
            }
        }
    }
}

void clearFOV(Entity *player) {
    int y, x;
    int RADIUS = 5;

    for (y = player->pos.y - RADIUS; y < player->pos.y + RADIUS; y++) {
        for (x = player->pos.x - RADIUS; x < player->pos.x + RADIUS; x++) {
            if (isInMap(y, x)) {
                if (map[y][x].monster != NULL) {
                    map[y][x].monster->monsterInfo->visible = false;
                }
                map[y][x].visible = false;
            }
        }
    }
}

int getDistance(Position origin, Position target) {
    double dy, dx;
    int d;

    dx = target.x - origin.x;
    dy = target.y - origin.y;
    d = (int)floor(sqrt(dx * dx + dy * dy));

    return d;
}

bool isInMap(int y, int x) {
    return (y >= 0 && y < MAP_HEIGHT && x >= 0 && x < MAP_WIDTH);
}

bool lineOfSight(Position origin, Position target) {
    int t, x, y, abs_delta_x, abs_delta_y, sign_x, sign_y, delta_x, delta_y;

    delta_x = origin.x - target.x;
    delta_y = origin.y - target.y;

    abs_delta_x = abs(delta_x);
    abs_delta_y = abs(delta_y);

    sign_x = getSign(delta_x);
    sign_y = getSign(delta_y);

    x = target.x;
    y = target.y;

    if (abs_delta_x > abs_delta_y) {
        t = abs_delta_y * 2 - abs_delta_x;

        do {
            if (!isInMap(y, x))
                return false;
            
            if (t >= 0) {
                y += sign_y;
                t -= abs_delta_x * 2;
            }

            x += sign_x;
            t += abs_delta_y * 2;

            if (x == origin.x && y == origin.y) {
                return true;
            }
        } while (map[y][x].transparent);

        return false;
    } else {
        t = abs_delta_x * 2 - abs_delta_y;

        do {
            if (!isInMap(y, x))
                return false;

            if (t >= 0) {
                x += sign_x;
                t -= abs_delta_y * 2;
            }

            y += sign_y;
            t += abs_delta_x * 2;

            if (x == origin.x && y == origin.y) {
                return true;
            }
        } while (map[y][x].transparent);

        return false;
    }
}

int getSign(int a) {
    if (a > 0) {
        return 1;
    }
    if (a < 0) {
        return -1;
    }
    return 0;
}