#include <stdlib.h>

#include "room.h"
#include "map.h"

Room createRoom(int y, int x, int height, int width) {
    Room newRoom;

    newRoom.pos.y = y;
    newRoom.pos.x = x;
    newRoom.height = height;
    newRoom.width = width;
    newRoom.center.y = y + (int)(height / 2);
    newRoom.center.x = x + (int)(width / 2);

    return newRoom;
}

void addRoomToMap(Room room) {
    for (int y = room.pos.y; y < room.pos.y + room.height; y++) {
        for (int x = room.pos.x; x < room.pos.x + room.width; x++) {
            map[y][x].ch = TILE_FLOOR;
            map[y][x].walkable = true;
            map[y][x].transparent = true;
        }
    }
}

void connectRoomCenters(Position center1, Position center2) {
    Position tmp = center1;

    while (true) {
        if (abs((tmp.x - 1) - center2.x) < abs(tmp.x - center2.x)) {
            tmp.x--;
        } else if (abs((tmp.x + 1) - center2.x) < abs(tmp.x - center2.x)) {
            tmp.x++;
        } else if (abs((tmp.y + 1) - center2.y) < abs(tmp.y - center2.y)) {
            tmp.y++;
        } else if (abs((tmp.y - 1) - center2.y) < abs(tmp.y - center2.y)) {
            tmp.y--;
        } else {
            break;
        }

        map[tmp.y][tmp.x].ch = TILE_FLOOR;
        map[tmp.y][tmp.x].walkable = true;
        map[tmp.y][tmp.x].transparent = true;
    }
}

bool roomOverlaps(Room *rooms, int counter, int y, int x, int height, int width) {
    for (int i = 0; i < counter; i++) {
        if (x >= rooms[i].pos.x + rooms[i].width || rooms[i].pos.x >= x + width) {
            continue;
        }
        if (y + height <= rooms[i].pos.y || rooms[i].pos.y + rooms[i].height <= y) {
            continue;
        }
        return true;
    }
    return false;
}