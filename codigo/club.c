#include <stdio.h>
#include <string.h>
#include "club.h"
#include "player.h"
#include "storage.h"

#define ORANGE "\033[38;5;208m"
#define BOLD   "\033[1m"
#define RESET  "\033[0m"

Club clubs[MAX_CLUBS];
int clubCount = 0;

void addClub(void) {
    if (clubCount >= MAX_CLUBS) {
        printf("%sLimite de equipas atingido!%s\n", ORANGE, RESET);
        return;
    }

    Club newClub;
    printf("\n%s=== NOVA EQUIPA ===%s\n", ORANGE BOLD, RESET);
    printf("Nome da equipa: ");
    scanf(" %49[^\n]", newClub.name);

    if (findClubIndex(newClub.name) != -1) {
        printf("%sEquipa já existe!%s\n", ORANGE, RESET);
        getchar(); getchar();
        return;
    }

    newClub.playerCount = 0;

    printf("\n%sMontando elenco da equipa %s%s\n", ORANGE, newClub.name, RESET);
    printf("Digite '0' como nome para parar (recomendado pelo menos 11 jogadores).\n\n");

    while (newClub.playerCount < MAX_PLAYERS_PER_CLUB) {
        char inputName[50];
        printf("Nome do jogador %d (ou '0'): ", newClub.playerCount + 1);
        scanf(" %49[^\n]", inputName);

        if (strcmp(inputName, "0") == 0) break;

        if (findPlayerIndex(inputName) != -1) {
            printf("%sNome já existe! Escolha outro.%s\n", ORANGE, RESET);
            continue;
        }

        Player newPlayer;
        strcpy(newPlayer.name, inputName);

        int shirt;
        int valid = 0;
        do {
            printf("Número da camisa (1-99): ");
            scanf("%d", &shirt);
            if (shirt < 1 || shirt > 99) {
                printf("%sNúmero inválido!%s\n", ORANGE, RESET);
                continue;
            }
            valid = 1;
            for (int j = 0; j < newClub.playerCount; j++) {
                Player *p = getPlayer(newClub.playerIndexes[j]);
                if (p->shirtNumber == shirt) {
                    printf("%sNúmero %d já usado por %s!%s\n", ORANGE, shirt, p->name, RESET);
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
        printf("%sJogador '%s' #%d adicionado com sucesso!%s\n\n", ORANGE, inputName, shirt, RESET);
    }

    clubs[clubCount++] = newClub;
    saveAllData();
    printf("%sEquipa '%s' criada com sucesso com %d jogadores!%s\n", ORANGE BOLD, newClub.name, newClub.playerCount, RESET);
    getchar(); getchar();
}

void listClubs(void) {
    if (clubCount == 0) {
        printf("%sNenhuma equipa cadastrada.%s\n", ORANGE, RESET);
        getchar(); getchar();
        return;
    }

    printf("\n%s=== EQUIPAS (%d) ===%s\n", ORANGE BOLD, clubCount, RESET);
    for (int i = 0; i < clubCount; i++) {
        printf("\n[%d] %s%s (%d jogadores)%s\n", i+1, ORANGE, clubs[i].name, clubs[i].playerCount, RESET);
        for (int j = 0; j < clubs[i].playerCount; j++) {
            Player *p = getPlayer(clubs[i].playerIndexes[j]);
            printf("  • %s%s #%d (%s)%s\n", ORANGE, p->name, p->shirtNumber, p->position, RESET);
        }
    }
    getchar(); getchar();
}

void viewClubs(void) {
    if (clubCount == 0) {
        printf("%sNenhuma equipa cadastrada.%s\n", ORANGE, RESET);
        printf("%sPressione ENTER para continuar...%s", ORANGE, RESET);
        getchar(); getchar();
        return;
    }

    printf("\n%s=== VISUALIZAÇÃO DE EQUIPAS (%d) ===%s\n", ORANGE BOLD, clubCount, RESET);
    for (int i = 0; i < clubCount; i++) {
        printf("\n[%d] %s%s (%d jogadores)%s\n", i+1, ORANGE, clubs[i].name, clubs[i].playerCount, RESET);
        for (int j = 0; j < clubs[i].playerCount; j++) {
            Player *p = getPlayer(clubs[i].playerIndexes[j]);
            printf("  • %s%s #%d (%s) - %s%s\n", ORANGE, p->name, p->shirtNumber, p->position, p->nationality, RESET);
        }
    }
    printf("\n%sPressione ENTER para voltar...%s", ORANGE, RESET);
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
        printf("\n%s--- GESTÃO DE EQUIPAS ---%s\n", ORANGE BOLD, RESET);
        printf("1. Adicionar equipa\n");
        printf("2. Listar equipas\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch (op) {
            case 1: addClub(); break;
            case 2: listClubs(); break;
            case 0: break;
            default: printf("%sOpção inválida!%s\n", ORANGE, RESET); getchar(); getchar();
        }
    } while (op != 0);
}