#ifndef MATCH_H
#define MATCH_H

#include "club.h"

typedef struct {
    Club *clubA;
    Club *clubB;

    int scoreA;
    int scoreB;

    int shotsA;
    int shotsOnTargetA;
    int foulsA;
    int cornersA;
    int yellowA;
    int redA;
    float possessionA;

    int shotsB;
    int shotsOnTargetB;
    int foulsB;
    int cornersB;
    int yellowB;
    int redB;
    float possessionB;
} Match;

void playMatch(Match *m);
void printMatch(Match m);

#endif
