#ifndef PLAYER_H
#define PLAYER_H

#include <utility>

class Player
{
    int ch;
    std::pair<int, int> pos;

public:
    Player(int ch, std::pair<int, int> pos);

    void draw(this const Player &self);
};

#endif // PLAYER_H