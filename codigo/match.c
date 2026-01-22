#include <stdio.h>               // Biblioteca padrão para entrada/saída (printf, scanf, getchar)
#include <stdlib.h>              // Para rand(), srand() (geração de resultados aleatórios) e outras funções do sistema
#include "match.h"               // Header com definição da struct Match e constantes (MAX_MATCHES, declarações de funções)
#include "club.h"                // Necessário para struct Club, getClub(), clubCount, listClubs(), etc.
#include "storage.h"             // Para saveAllData() (salvar jogos após cada partida)
#include "menu.h"                // Para clearScreen() e definições de cores (ORANGE, BOLD, RESET)

// Definições de cores ANSI (copiadas para independência do ficheiro menu.c)
#define ORANGE "\033[38;5;208m"  // Código ANSI para cor laranja no terminal
#define BOLD   "\033[1m"         // Código ANSI para texto em negrito
#define RESET  "\033[0m"         // Código ANSI para resetar cor e estilo

// Array global que armazena todos os jogos/partidas disputadas
Match matches[MAX_MATCHES];      // Cada posição é uma partida (struct Match)

// Contador global: mantém o número atual de partidas registradas (0 no início)
int matchCount = 0;

// Gera um resultado de partida completamente aleatório (placar e estatísticas)
void generateRandomMatch(Match *m) {
    m->scoreA = rand() % 6;                  // Gólos da equipa A (0 a 5)
    m->scoreB = rand() % 6;                  // Gólos da equipa B (0 a 5)

    m->possessionA = 30 + rand() % 41;       // Posse de bola da equipa A (30% a 70%)
    m->possessionB = 100 - m->possessionA;   // Posse da equipa B é o complemento (soma 100%)

    m->shotsA = 6 + rand() % 15 + m->scoreA * 2;         // Chutes totais da equipa A (base + aleatório + bónus por gólos)
    m->shotsB = 6 + rand() % 15 + m->scoreB * 2;         // Chutes totais da equipa B

    // Chutes no alvo: pelo menos os gólos + aleatório (limitado pelos chutes totais)
    m->shotsOnTargetA = m->scoreA + rand() % (m->shotsA - m->scoreA + 3);
    m->shotsOnTargetB = m->scoreB + rand() % (m->shotsB - m->scoreB + 3);
}

// Mostra o resultado de uma partida com formatação bonita e cores
void printMatchResult(const Match *m) {
    printf("\n%s===== RESULTADO =====%s\n", ORANGE BOLD, RESET);  // Cabeçalho em negrito laranja
    printf("%s %d x %d %s\n\n", m->clubA->name, m->scoreA, m->scoreB, m->clubB->name);  // Placar principal

    // Estatísticas da equipa A
    printf("%s%s: Chutes %d (%d no alvo) | Posse %d%%%s\n", ORANGE, m->clubA->name, m->shotsA, m->shotsOnTargetA, m->possessionA, RESET);
    // Estatísticas da equipa B
    printf("%s%s: Chutes %d (%d no alvo) | Posse %d%%%s\n", ORANGE, m->clubB->name, m->shotsB, m->shotsOnTargetB, m->possessionB, RESET);

    // Mensagem final de vitória ou empate com emoji
    if (m->scoreA > m->scoreB) {
        printf("\n%sVITÓRIA: %s! 🎉%s\n", ORANGE BOLD, m->clubA->name, RESET);
    } else if (m->scoreB > m->scoreA) {
        printf("\n%sVITÓRIA: %s! 🎉%s\n", ORANGE BOLD, m->clubB->name, RESET);
    } else {
        printf("\n%sEMPATE! 🤝%s\n", ORANGE BOLD, RESET);
    }
}

// Permite registar um jogo manual (utilizador escolhe as duas equipas)
void playManualMatch(void) {
    if (clubCount < 2) {                     // Verifica se há pelo menos 2 equipas para jogar
        printf("%sPrecisa de pelo menos 2 equipas!%s\n", ORANGE, RESET);
        printf("%sPressione ENTER para continuar...%s", ORANGE, RESET);
        getchar(); getchar();                // Espera ENTER para voltar ao menu
        return;
    }

    listClubs();                             // Mostra a lista de equipas para o utilizador escolher

    int a, b;                                // Variáveis para os índices das equipas escolhidas
    printf("\n%sEquipa A: %s", ORANGE, RESET); scanf("%d", &a); a--;  // Lê índice da equipa A (ajusta -1)
    printf("%sEquipa B: %s", ORANGE, RESET); scanf("%d", &b); b--;    // Lê índice da equipa B

    // Validação: equipas diferentes e índices válidos
    if (a == b || a < 0 || a >= clubCount || b < 0 || b >= clubCount) {
        printf("%sSeleção inválida!%s\n", ORANGE, RESET);
        printf("%sPressione ENTER para continuar...%s", ORANGE, RESET);
        getchar(); getchar();
        return;
    }

    Match m;                                 // Estrutura temporária para a partida
    m.clubA = getClub(a);                    // Obtém ponteiro para a equipa A
    m.clubB = getClub(b);                    // Obtém ponteiro para a equipa B
    generateRandomMatch(&m);                 // Gera placar e estatísticas aleatórias

    matches[matchCount++] = m;               // Adiciona a partida ao histórico global
    saveAllData();                           // Salva imediatamente no ficheiro

    printMatchResult(&m);                    // Mostra o resultado da partida
    printf("\n%sPressione ENTER para continuar...%s", ORANGE, RESET);
    getchar(); getchar();
}

// Sorteia aleatoriamente duas equipas e simula uma partida
void playRandomMatch(void) {
    if (clubCount < 8) {                     // Requisito mínimo de 8 equipas (podia ser 2, mas mantido como no teu código)
        printf("%sPrecisa de pelo menos 8 equipas!%s\n", ORANGE, RESET);
        printf("%sPressione ENTER para continuar...%s", ORANGE, RESET);
        getchar(); getchar();
        return;
    }

    int indices[50];                         // Array temporário para embaralhar índices
    for (int i = 0; i < clubCount; i++) indices[i] = i;  // Preenche com índices de 0 até clubCount-1

    // Algoritmo de Fisher-Yates para embaralhar os índices (garante aleatoriedade)
    for (int i = clubCount - 1; i > 0; i--) {
        int j = rand() % (i + 1);            // Escolhe posição aleatória
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    Match m;                                 // Estrutura temporária para a partida
    m.clubA = getClub(indices[0]);           // Primeira equipa sorteada
    m.clubB = getClub(indices[1]);           // Segunda equipa sorteada
    generateRandomMatch(&m);                 // Gera placar e estatísticas aleatórias

    matches[matchCount++] = m;               // Adiciona ao histórico
    saveAllData();                           // Salva no ficheiro

    printf("\n%sSORTEIO ALEATÓRIO: %s vs %s%s\n", ORANGE BOLD, m.clubA->name, m.clubB->name, RESET);
    printMatchResult(&m);                    // Mostra o resultado
    printf("\n%sPressione ENTER para continuar...%s", ORANGE, RESET);
    getchar(); getchar();
}

// Função que simula um torneio completo com 8 equipas (mata-mata: quartas, semis, 3º lugar e final)
void startTournament(void) {
    if (clubCount < 8) {                     // Verifica requisito mínimo de 8 equipas
        printf("%sPrecisa de pelo menos 8 equipas para iniciar um torneio!%s\n", ORANGE, RESET);
        printf("%sPressione ENTER para continuar...%s", ORANGE, RESET);
        getchar(); getchar();
        return;
    }

    clearScreen();                           // Limpa a tela para começar o torneio
    printf("%s=== TORNEIO AUTOMÁTICO (8 EQUIPAS) ===%s\n\n", ORANGE BOLD, RESET);
    printf("%sSelecionando os 8 primeiros clubes cadastrados...%s\n\n", ORANGE, RESET);

    // Seleciona os 8 primeiros clubes cadastrados
    Club *torneio[8];
    for (int i = 0; i < 8; i++) {
        torneio[i] = getClub(i);             // Obtém ponteiro para cada clube
        printf("%d. %s\n", i+1, torneio[i]->name);  // Mostra a lista inicial
    }

    printf("\n%sPressione ENTER para iniciar o torneio...%s", ORANGE, RESET);
    getchar(); getchar();                    // Espera confirmação do utilizador

    // Quartas de final (4 jogos)
    printf("\n%s=== QUARTAS DE FINAL ===%s\n", ORANGE BOLD, RESET);
    Match quartas[4];
    for (int i = 0; i < 4; i++) {
        quartas[i].clubA = torneio[i];       // Emparelha 1º vs 8º, 2º vs 7º, etc.
        quartas[i].clubB = torneio[7 - i];
        generateRandomMatch(&quartas[i]);    // Simula o jogo aleatoriamente
        matches[matchCount++] = quartas[i];  // Regista no histórico
        printMatchResult(&quartas[i]);       // Mostra resultado
        printf("\n%sPressione ENTER para o próximo jogo...%s", ORANGE, RESET);
        getchar(); getchar();                // Pausa entre jogos
    }

    // Semifinais (2 jogos)
    printf("\n%s=== SEMIFINAIS ===%s\n", ORANGE BOLD, RESET);
    Match semis[2];
    // Vencedor da primeira quartas vs vencedor da segunda
    semis[0].clubA = (quartas[0].scoreA > quartas[0].scoreB) ? quartas[0].clubA : quartas[0].clubB;
    semis[0].clubB = (quartas[1].scoreA > quartas[1].scoreB) ? quartas[1].clubA : quartas[1].clubB;
    generateRandomMatch(&semis[0]);
    matches[matchCount++] = semis[0];
    printMatchResult(&semis[0]);
    printf("\n%sPressione ENTER...%s", ORANGE, RESET);
    getchar(); getchar();

    // Vencedor da terceira vs vencedor da quarta
    semis[1].clubA = (quartas[2].scoreA > quartas[2].scoreB) ? quartas[2].clubA : quartas[2].clubB;
    semis[1].clubB = (quartas[3].scoreA > quartas[3].scoreB) ? quartas[3].clubA : quartas[3].clubB;
    generateRandomMatch(&semis[1]);
    matches[matchCount++] = semis[1];
    printMatchResult(&semis[1]);
    printf("\n%sPressione ENTER...%s", ORANGE, RESET);
    getchar(); getchar();

    // Disputa de 3º lugar (perdedores das semifinais)
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

    // Final (vencedores das semifinais)
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

    // Mostra o pódio final
    clearScreen();
    printf("\n%s=== PÓDIO DO TORNEIO ===%s\n\n", ORANGE BOLD, RESET);
    printf("%s🥇 1º LUGAR: %s%s\n", ORANGE BOLD, (final.scoreA > final.scoreB) ? final.clubA->name : final.clubB->name, RESET);
    printf("%s🥈 2º LUGAR: %s%s\n", ORANGE, (final.scoreA > final.scoreB) ? final.clubB->name : final.clubA->name, RESET);
    printf("%s🥉 3º LUGAR: %s%s\n", ORANGE, (disputa3.scoreA > disputa3.scoreB) ? disputa3.clubA->name : disputa3.clubB->name, RESET);

    saveAllData();                           // Salva todos os jogos do torneio
    printf("\n%sTorneio concluído com sucesso!%s\n", ORANGE BOLD, RESET);
    printf("%sPressione ENTER para voltar ao menu...%s", ORANGE, RESET);
    getchar(); getchar();
}

// Lista o histórico completo de partidas disputadas
void listMatchHistory(void) {
    if (matchCount == 0) {                   // Verifica se há partidas registradas
        printf("%sNenhum jogo registado.%s\n", ORANGE, RESET);
        printf("%sPressione ENTER para continuar...%s", ORANGE, RESET);
        getchar(); getchar();
        return;
    }

    printf("\n%s=== HISTÓRICO DE JOGOS (%d) ===%s\n", ORANGE BOLD, matchCount, RESET);
    for (int i = 0; i < matchCount; i++) {
        // Mostra cada partida com índice, equipas e placar
        printf("%d. %s %d x %d %s\n", i+1, matches[i].clubA->name, matches[i].scoreA, matches[i].scoreB, matches[i].clubB->name);
    }
    printf("\n%sPressione ENTER para continuar...%s", ORANGE, RESET);
    getchar(); getchar();
}

// Menu de registo de jogos (opções disponíveis para ADM)
void menuJogos(void) {
    int op;
    do {
        clearScreen();                       // Limpa a tela a cada ciclo do menu
        printf("\n%s--- REGISTO DE JOGOS ---%s\n", ORANGE BOLD, RESET);
        printf("1. Registar jogo manual\n");
        if (clubCount >= 2) printf("2. Sorteio aleatório\n");
        if (clubCount >= 8) printf("%s3. Iniciar Torneio (8 equipas)%s\n", ORANGE, RESET);
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch (op) {
            case 1: playManualMatch(); break;     // Chama função de jogo manual
            case 2: if (clubCount >= 2) playRandomMatch(); break;  // Chama sorteio aleatório
            case 3: if (clubCount >= 8) startTournament(); break;  // Inicia torneio completo
            case 0: break;                            // Sai do menu
            default: printf("%sOpção inválida!%s\n", ORANGE, RESET); getchar(); getchar();
        }
    } while (op != 0);                           // Repete até escolher 0
}