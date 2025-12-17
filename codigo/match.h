#ifndef MATCH_H
#define MATCH_H


#include "club.h"


typedef struct {
int goals;
int assists;
int fouls;
int shots;
} PlayerStats;


typedef struct {
Club *home;
Club *away;
int homeGoals;
int awayGoals;
} Match;


void playMatch(Match *m);
void printMatch(Match m);


#endif