#include <stdio.h>               // Biblioteca padrão para entrada/saída em ficheiros (fopen, fclose, fprintf, fscanf)
#include <string.h>              // Para funções como strcmp (usado em findClubIndex, embora aqui não diretamente)
#include "storage.h"             // Header com declarações das funções loadAllData e saveAllData
#include "player.h"              // Necessário para struct Player e array players[]
#include "club.h"                // Necessário para struct Club, clubCount, findClubIndex, getClub
#include "match.h"               // Necessário para struct Match, matchCount, matches[]

// Nome do ficheiro onde todos os dados são salvos/carregados (formato texto simples)
#define DATA_FILE "manager_data.txt"

// Declarações externas das variáveis globais definidas em outros ficheiros
extern Player players[MAX_PLAYERS];   // Array global de todos os jogadores
extern int playerCount;               // Número atual de jogadores cadastrados
extern Club clubs[MAX_CLUBS];         // Array global de todos os clubes
extern int clubCount;                 // Número atual de clubes cadastrados
extern Match matches[MAX_MATCHES];    // Array global de todas as partidas disputadas
extern int matchCount;                // Número atual de partidas registradas

// Função que carrega todos os dados salvos do ficheiro manager_data.txt
void loadAllData(void) {
    FILE *f = fopen(DATA_FILE, "r");  // Abre o ficheiro em modo leitura
    if (!f) return;                   // Se o ficheiro não existir ou não puder abrir, sai sem fazer nada

    // Lê a seção de jogadores
    fscanf(f, "PLAYERS %d\n", &playerCount);  // Lê o número total de jogadores
    for (int i = 0; i < playerCount; i++) {
        // Formato: nome|camisa|idade|nacionalidade|posição|último clube|clube atual|golos carreira
        fscanf(f, "%49[^|]|%d|%d|%49[^|]|%29[^|]|%49[^|]|%49[^|]|%d\n",
               players[i].name, &players[i].shirtNumber, &players[i].age,
               players[i].nationality, players[i].position,
               players[i].lastClub, players[i].currentClub, &players[i].careerGoals);
    }

    // Lê a seção de clubes
    fscanf(f, "CLUBS %d\n", &clubCount);  // Lê o número total de clubes
    for (int i = 0; i < clubCount; i++) {
        int dummy;                        // Variável temporária para ignorar o índice salvo (não usado aqui)
        fscanf(f, "%d|%49[^|]|%d", &dummy, clubs[i].name, &clubs[i].playerCount);
        // Lê os índices dos jogadores do elenco
        for (int j = 0; j < clubs[i].playerCount; j++) {
            fscanf(f, "|%d", &clubs[i].playerIndexes[j]);
        }
        fgetc(f);                         // Consome o '\n' final da linha
    }

    // Lê a seção de partidas/jogos
    fscanf(f, "MATCHES %d\n", &matchCount);  // Lê o número total de partidas
    for (int i = 0; i < matchCount; i++) {
        int aIdx, bIdx;                   // Índices dos clubes A e B no array clubs[]
        fscanf(f, "%d|%d|%d|%d|%d|%d|%d|%d|%d|%d\n",
               &aIdx, &bIdx,
               &matches[i].scoreA, &matches[i].scoreB,
               &matches[i].shotsA, &matches[i].shotsOnTargetA, &matches[i].possessionA,
               &matches[i].shotsB, &matches[i].shotsOnTargetB, &matches[i].possessionB);
        // Reconstrói os ponteiros para os clubes (usando os índices salvos)
        matches[i].clubA = getClub(aIdx);
        matches[i].clubB = getClub(bIdx);
    }

    fclose(f);                           // Fecha o ficheiro após leitura
}

// Função que salva todos os dados atuais no ficheiro manager_data.txt (sobrescreve o anterior)
void saveAllData(void) {
    FILE *f = fopen(DATA_FILE, "w");     // Abre o ficheiro em modo escrita (cria novo se não existir)
    if (!f) return;                      // Se não conseguir abrir/criar, sai sem salvar

    // Salva a seção de jogadores
    fprintf(f, "PLAYERS %d\n", playerCount);  // Escreve o número total de jogadores
    for (int i = 0; i < playerCount; i++) {
        // Formato: nome|camisa|idade|nacionalidade|posição|último clube|clube atual|golos carreira
        fprintf(f, "%s|%d|%d|%s|%s|%s|%s|%d\n",
                players[i].name, players[i].shirtNumber, players[i].age,
                players[i].nationality, players[i].position,
                players[i].lastClub, players[i].currentClub, players[i].careerGoals);
    }

    // Salva a seção de clubes
    fprintf(f, "CLUBS %d\n", clubCount);  // Escreve o número total de clubes
    for (int i = 0; i < clubCount; i++) {
        fprintf(f, "%d|%s|%d", i, clubs[i].name, clubs[i].playerCount);  // Salva índice, nome e quantidade de jogadores
        for (int j = 0; j < clubs[i].playerCount; j++) {
            fprintf(f, "|%d", clubs[i].playerIndexes[j]);  // Salva os índices de cada jogador do elenco
        }
        fprintf(f, "\n");                    // Finaliza a linha do clube
    }

    // Salva a seção de partidas/jogos
    fprintf(f, "MATCHES %d\n", matchCount);  // Escreve o número total de partidas
    for (int i = 0; i < matchCount; i++) {
        // Encontra os índices atuais dos clubes A e B (para salvar apenas números, não ponteiros)
        int aIdx = findClubIndex(matches[i].clubA->name);
        int bIdx = findClubIndex(matches[i].clubB->name);
        fprintf(f, "%d|%d|%d|%d|%d|%d|%d|%d|%d|%d\n",
                aIdx, bIdx,
                matches[i].scoreA, matches[i].scoreB,
                matches[i].shotsA, matches[i].shotsOnTargetA, matches[i].possessionA,
                matches[i].shotsB, matches[i].shotsOnTargetB, matches[i].possessionB);
    }

    fclose(f);                           // Fecha o ficheiro após escrita (garante que os dados sejam salvos)
}