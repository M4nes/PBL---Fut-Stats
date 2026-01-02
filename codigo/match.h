#ifndef MATCH_H
#define MATCH_H

#include "club.h"
#include <time.h>

#define MAX_MATCHES 200
#define MAX_DATE 20

typedef struct {
    Club *clubA;
    Club *clubB;
    
    int scoreA;
    int scoreB;
    
    int shotsA, shotsOnTargetA, possessionA;
    int shotsB, shotsOnTargetB, possessionB;
    
    char date[MAX_DATE];  // ex: "01/01/2026"
} Match;

// Funções
extern int matchCount;
void menuPartidas(void);
void playManualMatch(void);
void playRandomMatch(void);
void registerMatchStats(Match *m);
void printMatchResult(const Match *m);
void listMatchHistory(void);


#endif