#include "player.h"
#include "ctx.h"
#include "enemy.h"
#include "utils.h"
#include "win.h"
#include <ncurses.h>
#include <utility>

Player::Player(int ch, Position pos, int hp, int strength)
    : Entity(ch, pos), dungeon_level(1), xp(0), xp_level(1), xp_goal(5),
    potions(0)
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
        --new_pos.y;
        break;
    case Direction::South:
        ++new_pos.y;
        break;
    case Direction::East:
        ++new_pos.x;
        break;
    case Direction::West:
        --new_pos.x;
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
    auto action = static_cast<FightAction>(
        std::uniform_int_distribution
            (0, std::to_underlying(FightAction::FightActionCount) - 1)
            (g_ctx.randgen)
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

void Player::attack(Entity &target)
{
    const auto [tx, ty] = target.getPos();
    const auto [ex, ey] = this->getPos();
    const int dx = tx - ex;
    const int dy = ty - ey;

    if (std::abs(dx) + std::abs(dy) < 2)
        target.takeDamage(this->strength, *this);

    if (target.getHealth() <= 0) {
        int potion_drop_chances = std::uniform_int_distribution
            (0, 100)(g_ctx.randgen);

        if (potion_drop_chances <= 20)
            ++this->potions;

        this->xp += static_cast<Enemy &>(target).xp;
        if (this->xp >= this->xp_goal) {
            ++this->xp_level;
            this->xp = 0;
            this->xp_goal *= 2;
            this->max_hp += 5;
            this->hp += 5;
        }
    }
}

void Player::heal(this Player &self)
{
    int new_hp = self.hp;
    if (new_hp + 20 >= self.max_hp)
        new_hp = self.max_hp;
    else
        new_hp += 20;
    self.hp = new_hp;
}