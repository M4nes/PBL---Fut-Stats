#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "match.h"
#include "club.h"

Match matches[MAX_MATCHES];
int matchCount = 0;

void getCurrentDate(char *dateBuffer) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(dateBuffer, MAX_DATE, "%d/%m/%Y", tm_info);
}

void registerMatchStats(Match *m) {
    printf("\n===== REGISTRAR PARTIDA =====\n");
    printf("%s vs %s\n\n", m->clubA->name, m->clubB->name);

    printf("Gols %s: ", m->clubA->name);
    scanf("%d", &m->scoreA);
    printf("Gols %s: ", m->clubB->name);
    scanf("%d", &m->scoreB);

    printf("\n--- ESTATÍSTICAS %s ---\n", m->clubA->name);
    printf("Chutes: ");
    scanf("%d", &m->shotsA);
    printf("Chutes no alvo: ");
    scanf("%d", &m->shotsOnTargetA);
    printf("Posse de bola (%%): ");
    scanf("%d", &m->possessionA);

    printf("\n--- ESTATÍSTICAS %s ---\n", m->clubB->name);
    printf("Chutes: ");
    scanf("%d", &m->shotsB);
    printf("Chutes no alvo: ");
    scanf("%d", &m->shotsOnTargetB);
    printf("Posse de bola (%%): ");
    scanf("%d", &m->possessionB);

    // Validação simples de posse de bola
    if (m->possessionA + m->possessionB != 100) {
        printf("\nAviso: A soma da posse de bola não é 100%%. Ajustando automaticamente.\n");
        m->possessionB = 100 - m->possessionA;
    }

    getCurrentDate(m->date);
}

void printMatchResult(const Match *m) {
    printf("\n══════════════════════════════════\n");
    printf("         RESULTADO FINAL\n");
    printf("══════════════════════════════════\n");
    printf("  %s  %d  x  %d  %s\n", m->clubA->name, m->scoreA, m->scoreB, m->clubB->name);
    printf("  Data: %s\n\n", m->date);

    printf("  ── %s ──\n", m->clubA->name);
    printf("  Chutes: %d (%d no alvo) | Posse: %d%%\n", 
           m->shotsA, m->shotsOnTargetA, m->possessionA);

    printf("  ── %s ──\n", m->clubB->name);
    printf("  Chutes: %d (%d no alvo) | Posse: %d%%\n", 
           m->shotsB, m->shotsOnTargetB, m->possessionB);

    printf("══════════════════════════════════\n");

    // Mensagem de vencedor
    if (m->scoreA > m->scoreB) {
        printf("         VITÓRIA: %s ! 🎉\n", m->clubA->name);
    } else if (m->scoreB > m->scoreA) {
        printf("         VITÓRIA: %s ! 🎉\n", m->clubB->name);
    } else {
        printf("         EMPATE!\n");
    }
}

void playManualMatch(void) {
    if (getClubCount() < 2) {
        printf("\nVocê precisa de pelo menos 2 clubes para jogar uma partida!\n");
        printf("Pressione ENTER para voltar...");
        getchar(); getchar();
        return;
    }

    listClubs();

    printf("\nEscolha o número do Clube A: ");
    int a;
    scanf("%d", &a);
    a--;

    printf("Escolha o número do Clube B: ");
    int b;
    scanf("%d", &b);
    b--;

    if (a < 0 || a >= clubCount || b < 0 || b >= clubCount || a == b) {
        printf("\nSeleção de clubes inválida!\n");
        printf("Pressione ENTER para voltar...");
        getchar(); getchar();
        return;
    }

    Match newMatch;
    newMatch.clubA = getClub(a);
    newMatch.clubB = getClub(b);

    registerMatchStats(&newMatch);

    matches[matchCount] = newMatch;
    matchCount++;

    printMatchResult(&newMatch);

    printf("\nPartida registrada com sucesso!\n");
    printf("Pressione ENTER para continuar...");
    getchar(); getchar();
}

void playRandomMatch(void) {
    if (getClubCount() < 8) {
        printf("\nVocê precisa de pelo menos 8 clubes para ativar o sorteio aleatório!\n");
        printf("Clubes atuais: %d\n", getClubCount());
        printf("Pressione ENTER para voltar...");
        getchar(); getchar();
        return;
    }

    // Embaralha os índices dos clubes
    int indices[MAX_CLUBS];
    for (int i = 0; i < clubCount; i++) {
        indices[i] = i;
    }

    // Fisher-Yates shuffle
    for (int i = clubCount - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    // Pega os dois primeiros (já embaralhados)
    int a = indices[0];
    int b = indices[1];

    printf("\n🎲 SORTEIO ALEATÓRIO 🎲\n");
    printf("Confronto sorteado:\n\n");
    printf("       %s  VS  %s\n\n", clubs[a].name, clubs[b].name);

    printf("Quer registrar essa partida agora? (s/n): ");
    char resposta;
    scanf(" %c", &resposta);

    if (resposta != 's' && resposta != 'S') {
        printf("\nPartida cancelada. Voltando ao menu...\n");
        printf("Pressione ENTER para continuar...");
        getchar(); getchar();
        return;
    }

    Match newMatch;
    newMatch.clubA = getClub(a);
    newMatch.clubB = getClub(b);

    registerMatchStats(&newMatch);

    matches[matchCount] = newMatch;
    matchCount++;

    printMatchResult(&newMatch);

    printf("\nPartida registrada com sucesso!\n");
    printf("Pressione ENTER para continuar...");
    getchar(); getchar();
}

void listMatchHistory(void) {
    if (matchCount == 0) {
        printf("\nNenhum partida registrada ainda.\n");
        printf("Pressione ENTER para voltar...");
        getchar(); getchar();
        return;
    }

    printf("\n=== HISTÓRICO DE PARTIDAS (%d) ===\n", matchCount);
    for (int i = 0; i < matchCount; i++) {
        printf("\n[%d] %s %d x %d %s  |  %s\n", 
               i + 1,
               matches[i].clubA->name,
               matches[i].scoreA,
               matches[i].scoreB,
               matches[i].clubB->name,
               matches[i].date);
    }

    printf("\nDeseja ver os detalhes de alguma partida? (número ou 0 para voltar): ");
    int escolha;
    scanf("%d", &escolha);
    if (escolha > 0 && escolha <= matchCount) {
        printMatchResult(&matches[escolha - 1]);
        printf("\nPressione ENTER para voltar...");
        getchar(); getchar();
    }
}

void menuPartidas(void) {
    // Inicializa o rand apenas uma vez
    static int seeded = 0;
    if (!seeded) {
        srand(time(NULL));
        seeded = 1;
    }

    int op;
    do {
        printf("\n--- PARTIDAS ---\n");
        printf("1. Jogar partida manual\n");
        if (getClubCount() >= 8) {
            printf("2. Sortear confronto aleatório (🎲 ATIVADO! %d clubes)\n", getClubCount());
        } else {
            printf("2. Sortear confronto aleatório (precisa de 8+ clubes)\n");
        }
        printf("3. Ver histórico de partidas\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                playManualMatch();
                break;
            case 2:
                if (getClubCount() >= 8) {
                    playRandomMatch();
                } else {
                    printf("\nAinda não tem clubes suficientes para sorteio!\n");
                    getchar(); getchar();
                }
                break;
            case 3:
                listMatchHistory();
                break;
            case 0:
                break;
            default:
                printf("Opção inválida!\n");
                getchar(); getchar();
        }
    } while (op != 0);
}