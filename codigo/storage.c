#include <stdio.h>
#include <string.h>
#include "storage.h"
#include "player.h"
#include "club.h"
#include "match.h"

extern Player players[MAX_PLAYERS];
extern int playerCount;
extern Club clubs[MAX_CLUBS];
extern int clubCount;
extern Match matches[MAX_MATCHES];
extern int matchCount;

#define DATA_FILE "manager_data.txt"

void loadAllData(void) {
    FILE *file = fopen(DATA_FILE, "r");
    if (file == NULL) {
        printf("Nenhum save encontrado. Iniciando novo jogo!\n\n");
        return;
    }

    char line[256];

    // PLAYERS
    fgets(line, sizeof(line), file); // Pula cabeçalho ou versão
    fscanf(file, "PLAYERS %d\n", &playerCount);

    for (int i = 0; i < playerCount; i++) {
        fscanf(file, "%49[^|]|%d|%49[^|]|%29[^\n]\n",
               players[i].name,
               &players[i].age,
               players[i].nationality,
               players[i].position);
        strcpy(players[i].currentClub, "Sem clube");
        players[i].careerGoals = 0;
    }

    // CLUBS
    fscanf(file, "CLUBS %d\n", &clubCount);
    for (int i = 0; i < clubCount; i++) {
        int id;
        fscanf(file, "%d|%49[^|]|%d", &id, clubs[i].name, &clubs[i].playerCount);
        for (int j = 0; j < clubs[i].playerCount; j++) {
            fscanf(file, "|%d", &clubs[i].playerIndexes[j]);
        }
        fgetc(file); // consome \n

        // Atualiza currentClub dos jogadores
        for (int j = 0; j < clubs[i].playerCount; j++) {
            int pIdx = clubs[i].playerIndexes[j];
            if (pIdx >= 0 && pIdx < playerCount) {
                strcpy(players[pIdx].currentClub, clubs[i].name);
            }
        }
    }

    // MATCHES
    fscanf(file, "MATCHES %d\n", &matchCount);
    for (int i = 0; i < matchCount; i++) {
        int clubAIdx, clubBIdx;
        fscanf(file, "%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%19[^\n]\n",
               &clubAIdx, &clubBIdx,
               &matches[i].scoreA, &matches[i].scoreB,
               &matches[i].shotsA, &matches[i].shotsOnTargetA, &matches[i].possessionA,
               &matches[i].shotsB, &matches[i].shotsOnTargetB, &matches[i].possessionB,
               matches[i].date);

        matches[i].clubA = getClub(clubAIdx);
        matches[i].clubB = getClub(clubBIdx);
    }

    fclose(file);
    printf("Dados carregados com sucesso!\n");
    printf("%d jogadores, %d clubes e %d partidas encontradas.\n\n", playerCount, clubCount, matchCount);
}

void saveAllData(void) {
    FILE *file = fopen(DATA_FILE, "w");
    if (file == NULL) {
        printf("ERRO: Não foi possível salvar os dados!\n");
        return;
    }

    fprintf(file, "FUT STATS SAVE FILE v1.0\n");

    // PLAYERS
    fprintf(file, "PLAYERS %d\n", playerCount);
    for (int i = 0; i < playerCount; i++) {
        fprintf(file, "%s|%d|%s|%s\n",
                players[i].name,
                players[i].age,
                players[i].nationality,
                players[i].position);
    }

    // CLUBS
    fprintf(file, "CLUBS %d\n", clubCount);
    for (int i = 0; i < clubCount; i++) {
        fprintf(file, "%d|%s|%d", i, clubs[i].name, clubs[i].playerCount);
        for (int j = 0; j < clubs[i].playerCount; j++) {
            fprintf(file, "|%d", clubs[i].playerIndexes[j]);
        }
        fprintf(file, "\n");
    }

    // MATCHES
    fprintf(file, "MATCHES %d\n", matchCount);
    for (int i = 0; i < matchCount; i++) {
        int clubAIdx = -1, clubBIdx = -1;
        for (int j = 0; j < clubCount; j++) {
            if (clubs[j].name == matches[i].clubA->name) clubAIdx = j;
            if (clubs[j].name == matches[i].clubB->name) clubBIdx = j;
        }
        fprintf(file, "%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%s\n",
                clubAIdx, clubBIdx,
                matches[i].scoreA, matches[i].scoreB,
                matches[i].shotsA, matches[i].shotsOnTargetA, matches[i].possessionA,
                matches[i].shotsB, matches[i].shotsOnTargetB, matches[i].possessionB,
                matches[i].date);
    }

    fclose(file);
    printf("Dados salvos com sucesso em '%s'!\n", DATA_FILE);
}