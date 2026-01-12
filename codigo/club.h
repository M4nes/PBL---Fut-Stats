#ifndef CLUB_H
#define CLUB_H

#include "player.h"

#define MAX_CLUBS 50
#define MAX_PLAYERS_PER_CLUB 30
#define MAX_CLUB_NAME 50

typedef struct {
    char name[MAX_CLUB_NAME];
    int playerIndexes[MAX_PLAYERS_PER_CLUB];
    int playerCount;
} Club;

void menuEquipas(void);
void addClub(void);
void listClubs(void);

int getClubCount(void);
Club* getClub(int index);
int findClubIndex(const char *name);

extern Club clubs[MAX_CLUBS];
extern int clubCount;

#endif