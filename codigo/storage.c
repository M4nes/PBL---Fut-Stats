#include <stdio.h>
#include <string.h>
#include "storage.h"
#include "player.h"
#include "club.h"
#include "match.h"

#define DATA_FILE "manager_data.txt"

extern Player players[MAX_PLAYERS];
extern int playerCount;
extern Club clubs[MAX_CLUBS];
extern int clubCount;
extern Match matches[MAX_MATCHES];
extern int matchCount;

void loadAllData(void) {
    FILE *f = fopen(DATA_FILE, "r");
    if (!f) return;

    fscanf(f, "PLAYERS %d\n", &playerCount);
    for (int i = 0; i < playerCount; i++) {
        fscanf(f, "%49[^|]|%d|%d|%49[^|]|%29[^|]|%49[^|]|%49[^|]|%d\n",
               players[i].name, &players[i].shirtNumber, &players[i].age,
               players[i].nationality, players[i].position,
               players[i].lastClub, players[i].currentClub, &players[i].careerGoals);
    }

    fscanf(f, "CLUBS %d\n", &clubCount);
    for (int i = 0; i < clubCount; i++) {
        int dummy;
        fscanf(f, "%d|%49[^|]|%d", &dummy, clubs[i].name, &clubs[i].playerCount);
        for (int j = 0; j < clubs[i].playerCount; j++) {
            fscanf(f, "|%d", &clubs[i].playerIndexes[j]);
        }
        fgetc(f); // \n
    }

    fscanf(f, "MATCHES %d\n", &matchCount);
    for (int i = 0; i < matchCount; i++) {
        int aIdx, bIdx;
        fscanf(f, "%d|%d|%d|%d|%d|%d|%d|%d|%d|%d\n",
               &aIdx, &bIdx,
               &matches[i].scoreA, &matches[i].scoreB,
               &matches[i].shotsA, &matches[i].shotsOnTargetA, &matches[i].possessionA,
               &matches[i].shotsB, &matches[i].shotsOnTargetB, &matches[i].possessionB);
        matches[i].clubA = getClub(aIdx);
        matches[i].clubB = getClub(bIdx);
    }

    fclose(f);
}

void saveAllData(void) {
    FILE *f = fopen(DATA_FILE, "w");
    if (!f) return;

    fprintf(f, "PLAYERS %d\n", playerCount);
    for (int i = 0; i < playerCount; i++) {
        fprintf(f, "%s|%d|%d|%s|%s|%s|%s|%d\n",
                players[i].name, players[i].shirtNumber, players[i].age,
                players[i].nationality, players[i].position,
                players[i].lastClub, players[i].currentClub, players[i].careerGoals);
    }

    fprintf(f, "CLUBS %d\n", clubCount);
    for (int i = 0; i < clubCount; i++) {
        fprintf(f, "%d|%s|%d", i, clubs[i].name, clubs[i].playerCount);
        for (int j = 0; j < clubs[i].playerCount; j++) {
            fprintf(f, "|%d", clubs[i].playerIndexes[j]);
        }
        fprintf(f, "\n");
    }

    fprintf(f, "MATCHES %d\n", matchCount);
    for (int i = 0; i < matchCount; i++) {
        int aIdx = findClubIndex(matches[i].clubA->name);
        int bIdx = findClubIndex(matches[i].clubB->name);
        fprintf(f, "%d|%d|%d|%d|%d|%d|%d|%d|%d|%d\n",
                aIdx, bIdx,
                matches[i].scoreA, matches[i].scoreB,
                matches[i].shotsA, matches[i].shotsOnTargetA, matches[i].possessionA,
                matches[i].shotsB, matches[i].shotsOnTargetB, matches[i].possessionB);
    }

    fclose(f);
}