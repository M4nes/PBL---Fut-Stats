#include <stdio.h>
#include <stdlib.h>
#include "match.h"
#include "club.h"
#include "storage.h"

#define ORANGE "\033[38;5;208m"
#define BOLD   "\033[1m"
#define RESET  "\033[0m"

Match matches[MAX_MATCHES];
int matchCount = 0;

void generateRandomMatch(Match *m) {
    m->scoreA = rand() % 6;
    m->scoreB = rand() % 6;

    m->possessionA = 30 + rand() % 41;
    m->possessionB = 100 - m->possessionA;

    m->shotsA = 6 + rand() % 15 + m->scoreA * 2;
    m->shotsB = 6 + rand() % 15 + m->scoreB * 2;

    m->shotsOnTargetA = m->scoreA + rand() % (m->shotsA - m->scoreA + 3);
    m->shotsOnTargetB = m->scoreB + rand() % (m->shotsB - m->scoreB + 3);
}

void printMatchResult(const Match *m) {
    printf("\n%s===== RESULTADO =====%s\n", ORANGE BOLD, RESET);
    printf("%s %d x %d %s\n\n", m->clubA->name, m->scoreA, m->scoreB, m->clubB->name);
    printf("%s%s: Chutes %d (%d no alvo) | Posse %d%%%s\n", ORANGE, m->clubA->name, m->shotsA, m->shotsOnTargetA, m->possessionA, RESET);
    printf("%s%s: Chutes %d (%d no alvo) | Posse %d%%%s\n", ORANGE, m->clubB->name, m->shotsB, m->shotsOnTargetB, m->possessionB, RESET);

    if (m->scoreA > m->scoreB) {
        printf("\n%sVITÓRIA: %s! 🎉%s\n", ORANGE BOLD, m->clubA->name, RESET);
    } else if (m->scoreB > m->scoreA) {
        printf("\n%sVITÓRIA: %s! 🎉%s\n", ORANGE BOLD, m->clubB->name, RESET);
    } else {
        printf("\n%sEMPATE! %s\n", ORANGE BOLD, RESET);
    }
}

void playManualMatch(void) {
    if (clubCount < 2) {
        printf("%sPrecisa de pelo menos 2 equipas!%s\n", ORANGE, RESET);
        getchar(); getchar();
        return;
    }

    listClubs();
    int a, b;
    printf("\nEquipa A: "); scanf("%d", &a); a--;
    printf("Equipa B: "); scanf("%d", &b); b--;

    if (a == b || a < 0 || a >= clubCount || b < 0 || b >= clubCount) {
        printf("%sSeleção inválida!%s\n", ORANGE, RESET);
        getchar(); getchar();
        return;
    }

    Match m;
    m.clubA = getClub(a);
    m.clubB = getClub(b);
    generateRandomMatch(&m);

    matches[matchCount++] = m;
    saveAllData();

    printMatchResult(&m);
    getchar(); getchar();
}

void playRandomMatch(void) {
    if (clubCount < 8) {
        printf("%sPrecisa de pelo menos 8 equipas!%s\n", ORANGE, RESET);
        getchar(); getchar();
        return;
    }

    int indices[50];
    for (int i = 0; i < clubCount; i++) indices[i] = i;
    for (int i = clubCount - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    Match m;
    m.clubA = getClub(indices[0]);
    m.clubB = getClub(indices[1]);
    generateRandomMatch(&m);

    matches[matchCount++] = m;
    saveAllData();

    printf("\n%sSORTEIO ALEATÓRIO: %s vs %s%s\n", ORANGE BOLD, m.clubA->name, m.clubB->name, RESET);
    printMatchResult(&m);
    getchar(); getchar();
}

void listMatchHistory(void) {
    if (matchCount == 0) {
        printf("%sNenhum jogo registado.%s\n", ORANGE, RESET);
        getchar(); getchar();
        return;
    }

    printf("\n%s=== HISTÓRICO DE JOGOS ===%s\n", ORANGE BOLD, RESET);
    for (int i = 0; i < matchCount; i++) {
        printf("%d. %s %d x %d %s\n", i+1, matches[i].clubA->name, matches[i].scoreA, matches[i].scoreB, matches[i].clubB->name);
    }
    getchar(); getchar();
}

void menuJogos(void) {
    int op;
    do {
        printf("\n%s--- REGISTO DE JOGOS ---%s\n", ORANGE BOLD, RESET);
        printf("1. Registar jogo manual\n");
        if (clubCount >= 8) printf("2. Sorteio aleatório\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch (op) {
            case 1: playManualMatch(); break;
            case 2: if (clubCount >= 8) playRandomMatch(); break;
            case 0: break;
            default: printf("%sOpção inválida!%s\n", ORANGE, RESET); getchar(); getchar();
        }
    } while (op != 0);
}