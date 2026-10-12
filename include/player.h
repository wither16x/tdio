#ifndef PLAYER_H
#define PLAYER_H

#include <utility>

class Player
{
    int ch;
    std::pair<int, int> pos;

public:
    Player(int ch, std::pair<int, int> pos);

    int getChar(this const Player &self);
    std::pair<int, int> getPos(this const Player &self);
};

#endif // PLAYER_H