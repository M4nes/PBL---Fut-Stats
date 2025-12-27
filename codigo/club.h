#ifndef CLUB_H
#define CLUB_H
#include "player.h"

typedef struct {
    char name[50];
    int playerIndexes[50];
    int playerCount;
} Club;

void addClub();
void listClubs();
void editClub();

#endif
