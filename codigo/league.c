#include <stdio.h>
#include <stdlib.h>
#include "league.h"
#include "club.h"
#include "match.h"

typedef struct {
    Club *club;
    int points;
    int games;
    int wins;
    int draws;
    int losses;
    int goalsFor;
    int goalsAgainst;
    int goalDiff;
} LeagueEntry;

LeagueEntry league[MAX_CLUBS];

int compare(const void *a, const void *b) {
    LeagueEntry *ea = (LeagueEntry *)a;
    LeagueEntry *eb = (LeagueEntry *)b;
    if (ea->points != eb->points) return eb->points - ea->points;
    if (ea->goalDiff != eb->goalDiff) return eb->goalDiff - ea->goalDiff;
    return eb->goalsFor - ea->goalsFor;
}

void showLeagueTable(void) {
    for (int i = 0; i < clubCount; i++) {
        league[i].club = getClub(i);
        league[i].points = league[i].games = league[i].wins = league[i].draws = league[i].losses = 0;
        league[i].goalsFor = league[i].goalsAgainst = league[i].goalDiff = 0;
    }

    for (int i = 0; i < matchCount; i++) {
        Match m = matches[i];
        int a = findClubIndex(m.clubA->name);
        int b = findClubIndex(m.clubB->name);

        league[a].games++;
        league[b].games++;

        league[a].goalsFor += m.scoreA;
        league[a].goalsAgainst += m.scoreB;
        league[b].goalsFor += m.scoreB;
        league[b].goalsAgainst += m.scoreA;

        league[a].goalDiff = league[a].goalsFor - league[a].goalsAgainst;
        league[b].goalDiff = league[b].goalsFor - league[b].goalsAgainst;

        if (m.scoreA > m.scoreB) {
            league[a].points += 3;
            league[a].wins++;
            league[b].losses++;
        } else if (m.scoreB > m.scoreA) {
            league[b].points += 3;
            league[b].wins++;
            league[a].losses++;
        } else {
            league[a].points += 1;
            league[b].points += 1;
            league[a].draws++;
            league[b].draws++;
        }
    }

    qsort(league, clubCount, sizeof(LeagueEntry), compare);

    printf("\n=== CLASSIFICAÇÃO ===\n");
    printf("Pos | Equipa           | Pts | J  | V  | E  | D  | GM | GS | SG\n");
    for (int i = 0; i < clubCount; i++) {
        LeagueEntry e = league[i];
        printf("%3d | %-16s | %3d | %2d | %2d | %2d | %2d | %2d | %2d | %2d\n",
               i+1, e.club->name, e.points, e.games, e.wins, e.draws, e.losses,
               e.goalsFor, e.goalsAgainst, e.goalDiff);
    }
}