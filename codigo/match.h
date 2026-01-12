#ifndef MATCH_H
#define MATCH_H

#include "club.h"

#define MAX_MATCHES 200

typedef struct {
    Club *clubA;
    Club *clubB;
    int scoreA, scoreB;
    int shotsA, shotsOnTargetA, possessionA;
    int shotsB, shotsOnTargetB, possessionB;
} Match;

void menuJogos(void);
void playManualMatch(void);
void playRandomMatch(void);
void generateRandomMatch(Match *m);
void printMatchResult(const Match *m);
void listMatchHistory(void);

extern Match matches[MAX_MATCHES];
extern int matchCount;

#endif