#include <stdio.h>
#include <string.h>
#include "club.h"
#include "player.h"
#include "storage.h"

Club clubs[MAX_CLUBS];
int clubCount = 0;

void addClub(void) {
    if (clubCount >= MAX_CLUBS) {
        printf("Limite de equipas atingido!\n");
        return;
    }

    Club newClub;
    printf("\n=== NOVA EQUIPA ===\n");
    printf("Nome da equipa: ");
    scanf(" %49[^\n]", newClub.name);

    if (findClubIndex(newClub.name) != -1) {
        printf("Equipa já existe!\n");
        getchar(); getchar();
        return;
    }

    newClub.playerCount = 0;

    printf("\nMontando elenco da equipa %s\n", newClub.name);
    printf("Digite '0' como nome para parar (recomendado pelo menos 11 jogadores).\n\n");

    while (newClub.playerCount < MAX_PLAYERS_PER_CLUB) {
        char inputName[50];
        printf("Nome do jogador %d (ou '0'): ", newClub.playerCount + 1);
        scanf(" %49[^\n]", inputName);

        if (strcmp(inputName, "0") == 0) break;

        // Verifica se nome já existe
        if (findPlayerIndex(inputName) != -1) {
            printf("Nome já existe! Escolha outro.\n");
            continue;
        }

        Player newPlayer;
        strcpy(newPlayer.name, inputName);

        // Validação única do número da camisa no clube
        int shirt;
        int valid = 0;
        do {
            printf("Número da camisa (1-99): ");
            scanf("%d", &shirt);
            if (shirt < 1 || shirt > 99) {
                printf("Número inválido! Deve ser entre 1 e 99.\n");
                continue;
            }
            valid = 1;
            for (int j = 0; j < newClub.playerCount; j++) {
                Player *p = getPlayer(newClub.playerIndexes[j]);
                if (p->shirtNumber == shirt) {
                    printf("Número %d já usado por %s!\n", shirt, p->name);
                    valid = 0;
                    break;
                }
            }
        } while (!valid);
        newPlayer.shirtNumber = shirt;

        printf("Idade: ");
        scanf("%d", &newPlayer.age);

        printf("Nacionalidade: ");
        scanf(" %49[^\n]", newPlayer.nationality);

        printf("Posição: ");
        scanf(" %29[^\n]", newPlayer.position);

        printf("Último clube (ou 'Nenhum'): ");
        scanf(" %49[^\n]", newPlayer.lastClub);

        strcpy(newPlayer.currentClub, newClub.name);
        newPlayer.careerGoals = 0;

        players[playerCount] = newPlayer;
        newClub.playerIndexes[newClub.playerCount++] = playerCount++;
        printf("Jogador '%s' #%d adicionado!\n\n", inputName, shirt);
    }

    clubs[clubCount++] = newClub;
    saveAllData();
    printf("Equipa '%s' criada com %d jogadores!\n", newClub.name, newClub.playerCount);
    getchar(); getchar();
}

void listClubs(void) {
    if (clubCount == 0) {
        printf("\nNenhuma equipa cadastrada.\n");
        getchar(); getchar();
        return;
    }

    printf("\n=== EQUIPAS (%d) ===\n", clubCount);
    for (int i = 0; i < clubCount; i++) {
        printf("\n[%d] %s (%d jogadores)\n", i+1, clubs[i].name, clubs[i].playerCount);
        for (int j = 0; j < clubs[i].playerCount; j++) {
            Player *p = getPlayer(clubs[i].playerIndexes[j]);
            printf("  • %s #%d (%s)\n", p->name, p->shirtNumber, p->position);
        }
    }
    getchar(); getchar();
}

int getClubCount(void) {
    return clubCount;
}

Club* getClub(int index) {
    return (index >= 0 && index < clubCount) ? &clubs[index] : NULL;
}

int findClubIndex(const char *name) {
    for (int i = 0; i < clubCount; i++) {
        if (strcmp(clubs[i].name, name) == 0) return i;
    }
    return -1;
}

void menuEquipas(void) {
    int op;
    do {
        printf("\n--- GESTÃO DE EQUIPAS ---\n");
        printf("1. Adicionar equipa\n");
        printf("2. Listar equipas\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch (op) {
            case 1: addClub(); break;
            case 2: listClubs(); break;
            case 0: break;
            default: printf("Opção inválida!\n"); getchar(); getchar();
        }
    } while (op != 0);
}