#ifndef PLAYER_H
#define PLAYER_H

#include "utils.h"
#include <utility>

class Player
{
    int ch;
    std::pair<int, int> pos;

public:
    int dungeon_level;

    Player(int ch, std::pair<int, int> pos);

    int getChar(this const Player &self);
    std::pair<int, int> getPos(this const Player &self);

    void move(this Player &self, Direction direction);
    void teleport(this Player &self, std::pair<int, int> new_pos);

    bool isOnTile(this const Player &self, int tilech);
};

#endif // PLAYER_H