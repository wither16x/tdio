#pragma once

#define MESSAGE_LENGTH                  128

typedef struct {
    char info[MESSAGE_LENGTH];
    char playerStats[MESSAGE_LENGTH];
} MessageArea;

void initializeMessageArea(void);
void displayMessageArea(void);
void setInfoMessage(char* msg, ...);
void appendInfoMessage(char* msg, ...);
void setPlayerStatsMessage(char* msg, ...);
void clearInfoMessage(void);

extern MessageArea* messageArea;