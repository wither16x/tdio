#include "player.h"
#include "ctx.h"
#include "enemy.h"
#include "utils.h"
#include "win.h"
#include <ncurses.h>

Player::Player(int ch, std::pair<int, int> pos, int hp, int strength)
    : Entity(ch, pos), dungeon_level(1), xp(0), xp_level(1), xp_goal(5)
{
    this->hp = hp;
    this->max_hp = hp;
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
    std::mt19937 rng(g_ctx.randdev());
    auto action = static_cast<FightAction>(
        std::uniform_int_distribution
            (0, std::to_underlying(FightAction::FightActionCount) - 1)(rng)
    );

    if (action == FightAction::Hit) {
        g_ctx.msg_area.set("The {} hits you!", attacker.getName());
        this->hp -= count;
    } else {
        g_ctx.msg_area.set("The {} misses!", attacker.getName());
    }

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

void Player::attack(this Player &self, Entity &target)
{
    const auto [tx, ty] = target.getPos();
    const auto [ex, ey] = self.getPos();
    const int dx = tx - ex;
    const int dy = ty - ey;

    if (std::abs(dx) + std::abs(dy) < 2)
        target.takeDamage(self.strength, self);

    if (target.getHealth() <= 0) {
        self.xp += static_cast<Enemy &>(target).xp;
        if (self.xp >= self.xp_goal) {
            ++self.xp_level;
            self.xp = 0;
            self.xp_goal *= 2;
            self.max_hp += 5;
            self.hp += 5;
        }
    }
}