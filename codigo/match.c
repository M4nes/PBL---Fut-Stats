#include <stdio.h>
#include <stdlib.h>
#include "match.h"
#include "club.h"
#include "storage.h"
#include "menu.h"  // Para clearScreen e cores

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
        printf("\n%sEMPATE! 🤝%s\n", ORANGE BOLD, RESET);
    }
}

void playManualMatch(void) {
    if (clubCount < 2) {
        printf("%sPrecisa de pelo menos 2 equipas!%s\n", ORANGE, RESET);
        printf("%sPressione ENTER para continuar...%s", ORANGE, RESET);
        getchar(); getchar();
        return;
    }

    listClubs();
    int a, b;
    printf("\n%sEquipa A: %s", ORANGE, RESET); scanf("%d", &a); a--;
    printf("%sEquipa B: %s", ORANGE, RESET); scanf("%d", &b); b--;

    if (a == b || a < 0 || a >= clubCount || b < 0 || b >= clubCount) {
        printf("%sSeleção inválida!%s\n", ORANGE, RESET);
        printf("%sPressione ENTER para continuar...%s", ORANGE, RESET);
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
    printf("\n%sPressione ENTER para continuar...%s", ORANGE, RESET);
    getchar(); getchar();
}

void playRandomMatch(void) {
    if (clubCount < 8) {
        printf("%sPrecisa de pelo menos 8 equipas!%s\n", ORANGE, RESET);
        printf("%sPressione ENTER para continuar...%s", ORANGE, RESET);
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
    printf("\n%sPressione ENTER para continuar...%s", ORANGE, RESET);
    getchar(); getchar();
}

void startTournament(void) {
    if (clubCount < 8) {
        printf("%sPrecisa de pelo menos 8 equipas para iniciar um torneio!%s\n", ORANGE, RESET);
        printf("%sPressione ENTER para continuar...%s", ORANGE, RESET);
        getchar(); getchar();
        return;
    }

    clearScreen();
    printf("%s=== TORNEIO AUTOMÁTICO (8 EQUIPAS) ===%s\n\n", ORANGE BOLD, RESET);
    printf("%sSelecionando os 8 primeiros clubes cadastrados...%s\n\n", ORANGE, RESET);

    Club *torneio[8];
    for (int i = 0; i < 8; i++) {
        torneio[i] = getClub(i);
        printf("%d. %s\n", i+1, torneio[i]->name);
    }

    printf("\n%sPressione ENTER para iniciar o torneio...%s", ORANGE, RESET);
    getchar(); getchar();

    // Quartas de final
    printf("\n%s=== QUARTAS DE FINAL ===%s\n", ORANGE BOLD, RESET);
    Match quartas[4];
    for (int i = 0; i < 4; i++) {
        quartas[i].clubA = torneio[i];
        quartas[i].clubB = torneio[7 - i];
        generateRandomMatch(&quartas[i]);
        matches[matchCount++] = quartas[i];
        printMatchResult(&quartas[i]);
        printf("\n%sPressione ENTER para o próximo jogo...%s", ORANGE, RESET);
        getchar(); getchar();
    }

    // Semifinais
    printf("\n%s=== SEMIFINAIS ===%s\n", ORANGE BOLD, RESET);
    Match semis[2];
    semis[0].clubA = (quartas[0].scoreA > quartas[0].scoreB) ? quartas[0].clubA : quartas[0].clubB;
    semis[0].clubB = (quartas[1].scoreA > quartas[1].scoreB) ? quartas[1].clubA : quartas[1].clubB;
    generateRandomMatch(&semis[0]);
    matches[matchCount++] = semis[0];
    printMatchResult(&semis[0]);
    printf("\n%sPressione ENTER...%s", ORANGE, RESET);
    getchar(); getchar();

    semis[1].clubA = (quartas[2].scoreA > quartas[2].scoreB) ? quartas[2].clubA : quartas[2].clubB;
    semis[1].clubB = (quartas[3].scoreA > quartas[3].scoreB) ? quartas[3].clubA : quartas[3].clubB;
    generateRandomMatch(&semis[1]);
    matches[matchCount++] = semis[1];
    printMatchResult(&semis[1]);
    printf("\n%sPressione ENTER...%s", ORANGE, RESET);
    getchar(); getchar();

    // Disputa de 3º lugar
    printf("\n%s=== DISPUTA DE 3º LUGAR ===%s\n", ORANGE BOLD, RESET);
    Club *terceiroA = (semis[0].scoreA > semis[0].scoreB) ? semis[0].clubB : semis[0].clubA;
    Club *terceiroB = (semis[1].scoreA > semis[1].scoreB) ? semis[1].clubB : semis[1].clubA;
    Match disputa3;
    disputa3.clubA = terceiroA;
    disputa3.clubB = terceiroB;
    generateRandomMatch(&disputa3);
    matches[matchCount++] = disputa3;
    printMatchResult(&disputa3);
    printf("\n%sPressione ENTER...%s", ORANGE, RESET);
    getchar(); getchar();

    // Final
    printf("\n%s=== FINAL ===%s\n", ORANGE BOLD, RESET);
    Club *finalA = (semis[0].scoreA > semis[0].scoreB) ? semis[0].clubA : semis[0].clubB;
    Club *finalB = (semis[1].scoreA > semis[1].scoreB) ? semis[1].clubA : semis[1].clubB;
    Match final;
    final.clubA = finalA;
    final.clubB = finalB;
    generateRandomMatch(&final);
    matches[matchCount++] = final;
    printMatchResult(&final);
    printf("\n%sPressione ENTER...%s", ORANGE, RESET);
    getchar(); getchar();

    // Pódio
    clearScreen();
    printf("\n%s=== PÓDIO DO TORNEIO ===%s\n\n", ORANGE BOLD, RESET);
    printf("%s🥇 1º LUGAR: %s%s\n", ORANGE BOLD, (final.scoreA > final.scoreB) ? final.clubA->name : final.clubB->name, RESET);
    printf("%s🥈 2º LUGAR: %s%s\n", ORANGE, (final.scoreA > final.scoreB) ? final.clubB->name : final.clubA->name, RESET);
    printf("%s🥉 3º LUGAR: %s%s\n", ORANGE, (disputa3.scoreA > disputa3.scoreB) ? disputa3.clubA->name : disputa3.clubB->name, RESET);

    saveAllData();
    printf("\n%sTorneio concluído com sucesso!%s\n", ORANGE BOLD, RESET);
    printf("%sPressione ENTER para voltar ao menu...%s", ORANGE, RESET);
    getchar(); getchar();
}

void listMatchHistory(void) {
    if (matchCount == 0) {
        printf("%sNenhum jogo registado.%s\n", ORANGE, RESET);
        printf("%sPressione ENTER para continuar...%s", ORANGE, RESET);
        getchar(); getchar();
        return;
    }

    printf("\n%s=== HISTÓRICO DE JOGOS (%d) ===%s\n", ORANGE BOLD, matchCount, RESET);
    for (int i = 0; i < matchCount; i++) {
        printf("%d. %s %d x %d %s\n", i+1, matches[i].clubA->name, matches[i].scoreA, matches[i].scoreB, matches[i].clubB->name);
    }
    printf("\n%sPressione ENTER para continuar...%s", ORANGE, RESET);
    getchar(); getchar();
}

void menuJogos(void) {
    int op;
    do {
        clearScreen();
        printf("\n%s--- REGISTO DE JOGOS ---%s\n", ORANGE BOLD, RESET);
        printf("1. Registar jogo manual\n");
        if (clubCount >= 2) printf("2. Sorteio aleatório\n");
        if (clubCount >= 8) printf("%s3. Iniciar Torneio (8 equipas)%s\n", ORANGE, RESET);
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch (op) {
            case 1: playManualMatch(); break;
            case 2: if (clubCount >= 2) playRandomMatch(); break;
            case 3: if (clubCount >= 8) startTournament(); break;
            case 0: break;
            default: printf("%sOpção inválida!%s\n", ORANGE, RESET); getchar(); getchar();
        }
    } while (op != 0);
}