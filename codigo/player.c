#include <stdio.h>
#include <string.h>
#include "player.h"

Player players[MAX_PLAYERS];
int playerCount = 0;

int findPlayerIndex(const char *name) {
    for (int i = 0; i < playerCount; i++) {
        if (strcmp(players[i].name, name) == 0) return i;
    }
    return -1;
}

Player* getPlayer(int index) {
    return (index >= 0 && index < playerCount) ? &players[index] : NULL;
}

int getPlayerCount(void) {
    return playerCount;
}