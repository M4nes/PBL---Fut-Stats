#ifndef CLUB_H
#define CLUB_H


#include "player.h"


#define MAX_PLAYERS 30
#define MAX_CLUB_NAME 50


typedef struct {
char name[MAX_CLUB_NAME];
Player players[MAX_PLAYERS];
int playerCount;
} Club;


void createClub(Club *c);
void addPlayerToClub(Club *c);
void printClub(Club c);


#endif