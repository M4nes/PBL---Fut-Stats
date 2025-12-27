#include <stdio.h>
#include "match.h"

void playMatch(Match *m){
    printf("\n===== PARTIDA =====\n");
    printf("%s VS %s\n", m->clubA->name, m->clubB->name);

    printf("Gols %s: ", m->clubA->name); scanf("%d",&m->scoreA);
    printf("Gols %s: ", m->clubB->name); scanf("%d",&m->scoreB);

    printf("\n--- Estatisticas %s ---\n", m->clubA->name);
    printf("Chutes: "); scanf("%d",&m->shotsA);
    printf("No alvo: "); scanf("%d",&m->shotsOnTargetA);
    printf("Escanteios: "); scanf("%d",&m->cornersA);
    printf("Faltas: "); scanf("%d",&m->foulsA);
    printf("Amarelos: "); scanf("%d",&m->yellowA);
    printf("Vermelhos: "); scanf("%d",&m->redA);
    printf("Posse (%%): "); scanf("%f",&m->possessionA);

    printf("\n--- Estatisticas %s ---\n", m->clubB->name);
    printf("Chutes: "); scanf("%d",&m->shotsB);
    printf("No alvo: "); scanf("%d",&m->shotsOnTargetB);
    printf("Escanteios: "); scanf("%d",&m->cornersB);
    printf("Faltas: "); scanf("%d",&m->foulsB);
    printf("Amarelos: "); scanf("%d",&m->yellowB);
    printf("Vermelhos: "); scanf("%d",&m->redB);
    printf("Posse (%%): "); scanf("%f",&m->possessionB);

    m->clubA->totalGoals += m->scoreA;
    m->clubB->totalGoals += m->scoreB;
}

void printMatch(Match m){
    printf("\n===== RESULTADO =====\n");
    printf("%s %d x %d %s\n", m.clubA->name, m.scoreA, m.scoreB, m.clubB->name);

    printf("\n-- %s --\n", m.clubA->name);
    printf("Chutes: %d | No alvo: %d | Escanteios: %d\n", m.shotsA, m.shotsOnTargetA, m.cornersA);
    printf("Faltas: %d | Amarelos: %d | Vermelhos: %d | Posse: %.1f%%\n",
           m.foulsA, m.yellowA, m.redA, m.possessionA);

    printf("\n-- %s --\n", m.clubB->name);
    printf("Chutes: %d | No alvo: %d | Escanteios: %d\n", m.shotsB, m.shotsOnTargetB, m.cornersB);
    printf("Faltas: %d | Amarelos: %d | Vermelhos: %d | Posse: %.1f%%\n",
           m.foulsB, m.yellowB, m.redB, m.possessionB);
}
