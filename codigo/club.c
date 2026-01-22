#include <stdio.h>
#include <string.h>
#include <stdlib.h>  // Para rand() no modo automático
#include "club.h"
#include "player.h"
#include "storage.h"
#include "menu.h"    // Para clearScreen, ORANGE, etc.

// Declaração externa da variável global de main.c
extern int isAdm;

// Cores ANSI (copiadas para independência)
#define ORANGE "\033[38;5;208m"
#define BOLD   "\033[1m"
#define RESET  "\033[0m"

Club clubs[MAX_CLUBS];
int clubCount = 0;

// Função de visualização simples (para usuário comum)
void viewClubs(void) {
    if (clubCount == 0) {
        printf("%sNenhuma equipa cadastrada.%s\n", ORANGE, RESET);
        printf("%sPressione ENTER para continuar...%s", ORANGE, RESET);
        getchar(); getchar();
        return;
    }

    clearScreen();
    printf("\n%s=== VISUALIZAÇÃO DE EQUIPAS (%d) ===%s\n", ORANGE BOLD, clubCount, RESET);
    for (int i = 0; i < clubCount; i++) {
        printf("\n[%d] %s%s (%d jogadores)%s\n", i+1, ORANGE, clubs[i].name, clubs[i].playerCount, RESET);
        for (int j = 0; j < clubs[i].playerCount; j++) {
            Player *p = getPlayer(clubs[i].playerIndexes[j]);
            printf("  • %s%s #%d (%s) - %s, %d anos%s\n", ORANGE, p->name, p->shirtNumber, p->position, p->nationality, p->age, RESET);
        }
    }
    printf("\n%sPressione ENTER para voltar...%s", ORANGE, RESET);
    getchar(); getchar();
}

// Adicionar equipa
void addClub(void) {
    if (clubCount >= MAX_CLUBS) {
        printf("%sLimite de equipas atingido!%s\n", ORANGE, RESET);
        return;
    }

    Club newClub;
    clearScreen();
    printf("\n%s=== NOVA EQUIPA ===%s\n", ORANGE BOLD, RESET);
    printf("Nome da equipa: ");
    scanf(" %49[^\n]", newClub.name);

    if (findClubIndex(newClub.name) != -1) {
        printf("%sEquipa já existe!%s\n", ORANGE, RESET);
        getchar(); getchar();
        return;
    }

    newClub.playerCount = 0;

    int modo;
    do {
        printf("\n%sModo de adição de jogadores:%s\n", ORANGE, RESET);
        printf("1. Manual (digitar um por um)\n");
        printf("2. Automático (11 jogadores aleatórios)\n");
        printf("Escolha: ");
        scanf("%d", &modo);
    } while (modo != 1 && modo != 2);

    if (modo == 1) {
        // Manual
        while (newClub.playerCount < MAX_PLAYERS_PER_CLUB) {
            char inputName[50];
            printf("Nome do jogador %d (ou '0' para parar): ", newClub.playerCount + 1);
            scanf(" %49[^\n]", inputName);

            if (strcmp(inputName, "0") == 0) break;

            if (findPlayerIndex(inputName) != -1) {
                printf("%sNome já existe!%s\n", ORANGE, RESET);
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
            printf("%sJogador '%s' #%d adicionado!%s\n\n", ORANGE, inputName, shirt, RESET);
        }
    } else {
        // Automático: 11 jogadores aleatórios
        printf("%sGerando 11 jogadores automáticos...%s\n", ORANGE, RESET);
        const char *nomes[] = {"João Silva", "Pedro Santos", "Lucas Oliveira", "Mateus Costa", "Gabriel Souza", "Rafael Pereira", "Felipe Almeida", "Bruno Rodrigues", "Vinicius Lima", "Thiago Ferreira", "Leonardo Martins"};
        const char *posicoes[] = {"Goleiro", "Zagueiro", "Lateral", "Volante", "Meia", "Atacante"};

        for (int i = 0; i < 11; i++) {
            Player newPlayer;
            sprintf(newPlayer.name, "%s %d", nomes[i % 11], i+1);
            newPlayer.shirtNumber = i+1;
            newPlayer.age = 18 + rand() % 18;
            strcpy(newPlayer.nationality, "Brasil");
            strcpy(newPlayer.position, posicoes[rand() % 6]);
            strcpy(newPlayer.lastClub, "Formação");
            strcpy(newPlayer.currentClub, newClub.name);
            newPlayer.careerGoals = 0;

            players[playerCount] = newPlayer;
            newClub.playerIndexes[newClub.playerCount++] = playerCount++;
        }
        printf("%s11 jogadores gerados!%s\n", ORANGE, RESET);
    }

    clubs[clubCount++] = newClub;
    saveAllData();
    printf("%sEquipa '%s' criada com sucesso!%s\n", ORANGE BOLD, newClub.name, RESET);
    getchar(); getchar();
}

void listClubs(void) {
    if (clubCount == 0) {
        printf("%sNenhuma equipa cadastrada.%s\n", ORANGE, RESET);
        getchar(); getchar();
        return;
    }

    clearScreen();
    printf("\n%s=== LISTA DE EQUIPAS (%d) ===%s\n", ORANGE BOLD, clubCount, RESET);
    for (int i = 0; i < clubCount; i++) {
        printf("\n[%d] %s%s (%d jogadores)%s\n", i+1, ORANGE, clubs[i].name, clubs[i].playerCount, RESET);
        for (int j = 0; j < clubs[i].playerCount; j++) {
            Player *p = getPlayer(clubs[i].playerIndexes[j]);
            printf("  • %s%s #%d (%s)%s\n", ORANGE, p->name, p->shirtNumber, p->position, RESET);
        }
    }
    printf("\n%sPressione ENTER para continuar...%s", ORANGE, RESET);
    getchar(); getchar();
}

void editClub(void) {
    if (clubCount == 0) {
        printf("%sNenhuma equipa para editar.%s\n", ORANGE, RESET);
        getchar(); getchar();
        return;
    }

    listClubs();

    printf("\n%sDigite o número da equipa para editar (0 para cancelar): %s", ORANGE, RESET);
    int choice;
    scanf("%d", &choice);
    if (choice == 0) return;
    choice--;

    if (choice < 0 || choice >= clubCount) {
        printf("%sEquipa inválida!%s\n", ORANGE, RESET);
        getchar(); getchar();
        return;
    }

    Club *c = &clubs[choice];

    int op;
    do {
        clearScreen();
        printf("\n%sEditar Equipa: %s%s\n", ORANGE BOLD, c->name, RESET);
        printf("1. Renomear equipa\n");
        printf("2. Adicionar jogador\n");
        printf("3. Remover jogador\n");
        printf("4. Remover equipa inteira\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                printf("Novo nome: ");
                scanf(" %49[^\n]", c->name);
                // Atualiza currentClub de todos os jogadores
                for (int j = 0; j < c->playerCount; j++) {
                    Player *p = getPlayer(c->playerIndexes[j]);
                    strcpy(p->currentClub, c->name);
                }
                saveAllData();
                printf("%sNome alterado!%s\n", ORANGE, RESET);
                break;
            case 2:
                if (c->playerCount >= MAX_PLAYERS_PER_CLUB) {
                    printf("%sElenco cheio!%s\n", ORANGE, RESET);
                    break;
                }
                printf("Nome do jogador (deve existir): ");
                char name[50];
                scanf(" %49[^\n]", name);
                int idx = findPlayerIndex(name);
                if (idx == -1) {
                    printf("%sJogador não encontrado!%s\n", ORANGE, RESET);
                } else {
                    int already = 0;
                    for (int j = 0; j < c->playerCount; j++) {
                        if (c->playerIndexes[j] == idx) already = 1;
                    }
                    if (already) {
                        printf("%sJogador já está no elenco!%s\n", ORANGE, RESET);
                    } else {
                        c->playerIndexes[c->playerCount++] = idx;
                        Player *p = getPlayer(idx);
                        strcpy(p->currentClub, c->name);
                        saveAllData();
                        printf("%sJogador adicionado!%s\n", ORANGE, RESET);
                    }
                }
                break;
            case 3:
                if (c->playerCount == 0) {
                    printf("%sElenco vazio!%s\n", ORANGE, RESET);
                    break;
                }
                printf("Número do jogador para remover (1 a %d): ", c->playerCount);
                int rem;
                scanf("%d", &rem);
                rem--;
                if (rem < 0 || rem >= c->playerCount) {
                    printf("%sNúmero inválido!%s\n", ORANGE, RESET);
                } else {
                    int playerIdx = c->playerIndexes[rem];
                    Player *p = getPlayer(playerIdx);
                    strcpy(p->currentClub, "Sem clube");
                    for (int k = rem; k < c->playerCount - 1; k++) {
                        c->playerIndexes[k] = c->playerIndexes[k + 1];
                    }
                    c->playerCount--;
                    saveAllData();
                    printf("%sJogador removido do elenco!%s\n", ORANGE, RESET);
                }
                break;
            case 4:
                printf("%sTem certeza que quer REMOVER a equipa '%s'? (s/n): %s", ORANGE, c->name, RESET);
                char confirm;
                scanf(" %c", &confirm);
                if (confirm == 's' || confirm == 'S') {
                    // Libera jogadores
                    for (int j = 0; j < c->playerCount; j++) {
                        Player *p = getPlayer(c->playerIndexes[j]);
                        strcpy(p->currentClub, "Sem clube");
                    }
                    // Remove da lista
                    for (int i = choice; i < clubCount - 1; i++) {
                        clubs[i] = clubs[i + 1];
                    }
                    clubCount--;
                    saveAllData();
                    printf("%sEquipa removida com sucesso!%s\n", ORANGE, RESET);
                    return;
                }
                break;
            case 0:
                break;
            default:
                printf("%sOpção inválida!%s\n", ORANGE, RESET);
        }

        if (op != 0) {
            printf("%sPressione ENTER para continuar...%s", ORANGE, RESET);
            getchar(); getchar();
        }
    } while (op != 0);
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
    if (!isAdm) {
        viewClubs();  // Usuário só vê
        return;
    }

    int op;
    do {
        clearScreen();
        printf("\n%s--- GESTÃO DE EQUIPAS (ADM) ---%s\n", ORANGE BOLD, RESET);
        printf("1. Adicionar equipa\n");
        printf("2. Listar equipas\n");
        printf("3. Editar equipa\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch (op) {
            case 1: addClub(); break;
            case 2: listClubs(); break;
            case 3: editClub(); break;
            case 0: break;
            default: printf("%sOpção inválida!%s\n", ORANGE, RESET); getchar(); getchar();
        }
    } while (op != 0);
}