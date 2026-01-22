#include <stdio.h>               // Biblioteca padrão para entrada/saída (printf, scanf)
#include <stdlib.h>              // Necessária para qsort() (ordenação da tabela)
#include "league.h"              // Header com declaração da função showLeagueTable()
#include "club.h"                // Necessário para struct Club, getClub(), findClubIndex(), clubCount
#include "match.h"               // Necessário para struct Match, matches[], matchCount

// Estrutura temporária usada apenas para calcular e ordenar a classificação
typedef struct {
    Club *club;                  // Ponteiro para o clube/equipa
    int points;                  // Pontos acumulados (3 por vitória, 1 por empate)
    int games;                   // Número de jogos disputados
    int wins;                    // Número de vitórias
    int draws;                   // Número de empates
    int losses;                  // Número de derrotas
    int goalsFor;                // Gólos marcados (GM)
    int goalsAgainst;            // Gólos sofridos (GS)
    int goalDiff;                // Diferença de gólos (SG = GM - GS)
} LeagueEntry;

// Array global temporário usado para calcular a tabela de classificação
LeagueEntry league[MAX_CLUBS];   // Uma entrada para cada clube (máximo = MAX_CLUBS)

// Função de comparação para qsort(): ordena por pontos, depois saldo de gólos, depois gólos marcados
int compare(const void *a, const void *b) {
    LeagueEntry *ea = (LeagueEntry *)a;   // Converte ponteiro genérico para struct LeagueEntry
    LeagueEntry *eb = (LeagueEntry *)b;

    // Primeiro critério: quem tem mais pontos fica acima (ordem decrescente)
    if (ea->points != eb->points) return eb->points - ea->points;

    // Segundo critério: maior saldo de gólos (goalDiff)
    if (ea->goalDiff != eb->goalDiff) return eb->goalDiff - ea->goalDiff;

    // Terceiro critério: quem marcou mais gólos (goalsFor)
    return eb->goalsFor - ea->goalsFor;
}

// Função principal: calcula e mostra a tabela de classificação completa
void showLeagueTable(void) {
    // Inicializa todas as entradas da tabela com valores zerados
    for (int i = 0; i < clubCount; i++) {
        league[i].club = getClub(i);               // Associa o clube correspondente
        league[i].points = 0;                      // Zera pontos
        league[i].games = 0;                       // Zera jogos
        league[i].wins = 0;                        // Zera vitórias
        league[i].draws = 0;                       // Zera empates
        league[i].losses = 0;                      // Zera derrotas
        league[i].goalsFor = 0;                    // Zera gólos marcados
        league[i].goalsAgainst = 0;                // Zera gólos sofridos
        league[i].goalDiff = 0;                    // Zera saldo de gólos
    }

    // Percorre todos os jogos já disputados e acumula estatísticas
    for (int i = 0; i < matchCount; i++) {
        Match m = matches[i];                      // Jogo atual

        // Encontra os índices dos dois clubes no array global
        int a = findClubIndex(m.clubA->name);
        int b = findClubIndex(m.clubB->name);

        // Incrementa o número de jogos disputados para ambos
        league[a].games++;
        league[b].games++;

        // Acumula gólos marcados e sofridos
        league[a].goalsFor += m.scoreA;
        league[a].goalsAgainst += m.scoreB;
        league[b].goalsFor += m.scoreB;
        league[b].goalsAgainst += m.scoreA;

        // Calcula saldo de gólos (diferença) para cada equipa
        league[a].goalDiff = league[a].goalsFor - league[a].goalsAgainst;
        league[b].goalDiff = league[b].goalsFor - league[b].goalsAgainst;

        // Atualiza pontos, vitórias, empates e derrotas
        if (m.scoreA > m.scoreB) {                 // Vitória da equipa A
            league[a].points += 3;                 // 3 pontos para o vencedor
            league[a].wins++;                      // +1 vitória
            league[b].losses++;                    // +1 derrota
        } else if (m.scoreB > m.scoreA) {          // Vitória da equipa B
            league[b].points += 3;
            league[b].wins++;
            league[a].losses++;
        } else {                                   // Empate
            league[a].points += 1;                 // 1 ponto para cada
            league[b].points += 1;
            league[a].draws++;                     // +1 empate
            league[b].draws++;
        }
    }

    // Ordena a tabela usando a função compare (ordem decrescente: mais pontos primeiro)
    qsort(league, clubCount, sizeof(LeagueEntry), compare);

    // Mostra o cabeçalho da tabela de classificação
    printf("\n=== CLASSIFICAÇÃO ===\n");
    printf("Pos | Equipa           | Pts | J | V | E | D | GM | GS | SG\n");

    // Mostra cada linha da tabela classificativa
    for (int i = 0; i < clubCount; i++) {
        LeagueEntry e = league[i];
        // Formatação: posição (i+1), nome alinhado à esquerda, números alinhados
        printf("%3d | %-16s | %3d | %2d | %2d | %2d | %2d | %2d | %2d | %2d\n",
               i+1, e.club->name, e.points, e.games, e.wins, e.draws, e.losses,
               e.goalsFor, e.goalsAgainst, e.goalDiff);
    }
}