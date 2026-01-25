#pragma once

#include <stdbool.h>

#include "position.h"

typedef struct {
    int height;
    int width;
    Position pos;
    Position center;
} Room;

Room createRoom(int y, int x, int height, int width);
void addRoomToMap(Room room);
bool roomOverlaps(Room* rooms, int counter, int y, int x, int height, int width);
void connectRoomCenters(Position center1, Position center2);