#include "player.h"
#include "ctx.h"
#include "utils.h"
#include "win.h"
#include <ncurses.h>

Player::Player(int ch, std::pair<int, int> pos, int hp, int strength)
    : Entity(ch, pos), dungeon_level(1)
{
    this->hp = hp;
    this->strength = strength;
    this->name = "Player";
}

void Player::move(Direction direction)
{
    auto new_pos = this->pos;

    switch (direction) {
    case Direction::North:
        --new_pos.second;
        break;
    case Direction::South:
        ++new_pos.second;
        break;
    case Direction::East:
        ++new_pos.first;
        break;
    case Direction::West:
        --new_pos.first;
        break;
    }

    for (std::size_t i = 1; i < g_ctx.entities.size(); i++) {
        if (g_ctx.entities[i]->getPos() == new_pos) {
            this->attack(*g_ctx.entities[i]);
            return;
        }
    }

    this->setPos(new_pos);
}

void Player::takeDamage(int count, const Entity &attacker)
{
    g_ctx.msg_area.set("The {} hits you!", attacker.getName());
    this->hp -= count;

    if (this->hp <= 0) {
        g_ctx.msg_area.set("You have been killed by a {}.", attacker.getName());
        g_ctx.msg_area.display();
        getch();
        g_ctx.running = false;
        g_ctx.painter.clearScreen();
        mvprintw(WINDOW_HEIGHT / 2, WINDOW_WIDTH / 2, "GAME OVER");
        getch();
    }
}

void Player::attack(this const Player &self, Entity &target)
{
    const auto [tx, ty] = target.getPos();
    const auto [ex, ey] = self.getPos();
    const int dx = tx - ex;
    const int dy = ty - ey;

    if (std::abs(dx) + std::abs(dy) < 2)
        target.takeDamage(self.strength, self);
}