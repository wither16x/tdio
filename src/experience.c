#include "experience.h"
#include "entity.h"

void getExperience(int amount) {
    player->playerInfo->xp += amount;
    if (player->playerInfo->xp >= player->playerInfo->requiredXP) {
        player->playerInfo->level++;
        player->playerInfo->requiredXP = player->playerInfo->xp + player->playerInfo->requiredXP * 2;
        player->hp += 2;
        player->maxHP += 2;
        player->strength++;
    }
}