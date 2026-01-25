#include "message.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "map.h"

void initializeMessageArea(void) {
    MessageArea* newMessageArea = calloc(1, sizeof(MessageArea));
    messageArea = newMessageArea;
}

void displayMessageArea(void) {
    mvprintw(MAP_HEIGHT + 1, 0, "%s", messageArea->info);

    mvprintw(MAP_HEIGHT + 2, 0, "%s", messageArea->playerStats);
}

void setInfoMessage(char* msg, ...) {
    char buffer[MESSAGE_LENGTH];
    va_list args;
    
    va_start(args, msg);
    vsnprintf(buffer, sizeof(buffer), msg, args);
    va_end(args);

    strncpy(messageArea->info, buffer, sizeof(messageArea->info) - 1);
    messageArea->info[sizeof(messageArea->info) - 1] = '\0';
}

void setPlayerStatsMessage(char *msg, ...) {
    char buffer[MESSAGE_LENGTH];
    va_list args;

    va_start(args, msg);
    vsnprintf(buffer, sizeof(buffer), msg, args);
    va_end(args);

    strncpy(messageArea->playerStats, buffer, sizeof(messageArea->playerStats) - 1);
    messageArea->playerStats[sizeof(messageArea->playerStats) - 1] = '\0';
}

void clearInfoMessage(void) {
    memset(messageArea->info, 0, sizeof(messageArea->info));
}