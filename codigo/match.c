#include <stdio.h>
#include "match.h"

void playMatch(Match *m) {
    printf("\n=== JOGO ===\n");
    printf("%s vs %s\n", m->home->name, m->away->name);

    printf("Gols do %s: ", m->home->name);
    scanf("%d", &m->homeGoals);

    printf("Gols do %s: ", m->away->name);
    scanf("%d", &m->awayGoals);
    getchar();
}

void printMatch(Match m) {
    printf("\nResultado Final:\n");
    printf("%s %d x %d %s\n",
           m.home->name,
           m.homeGoals,
           m.awayGoals,
           m.away->name);
}
