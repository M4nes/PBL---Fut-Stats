#include <stdio.h>
#include <string.h>
#include "club.h"
#include "player.h"
#include "storage.h"

Club clubs[MAX_CLUBS];
int clubCount = 0;

void addClub(void) {
    if (clubCount >= MAX_CLUBS) {
        printf("\nLimite de clubes atingido (%d)!\n", MAX_CLUBS);
        return;
    }

    Club newClub;
    printf("\n=== ADICIONAR CLUBE ===\n");
    printf("Nome do clube: ");
    scanf(" %49[^\n]", newClub.name);

    if (findClubIndex(newClub.name) != -1) {
        printf("\nJá existe um clube com esse nome!\n");
        printf("Pressione ENTER para continuar...");
        getchar(); getchar();
        return;
    }

    newClub.playerCount = 0;

    printf("\nMontando elenco do %s!\n", newClub.name);
    printf("Digite o nome do jogador. Se não existir, será criado com número e posição.\n");
    printf("Digite '0' para parar (recomendado pelo menos 11 jogadores).\n\n");

    while (1) {
        if (newClub.playerCount >= MAX_PLAYERS_PER_CLUB) {
            printf("\nLimite de jogadores no clube atingido!\n");
            break;
        }

        char inputName[MAX_NAME];
        printf("Nome do jogador %d (ou '0' para parar): ", newClub.playerCount + 1);
        scanf(" %49[^\n]", inputName);

        if (strcmp(inputName, "0") == 0) {
            if (newClub.playerCount < 8) {
                printf("\nAviso: Elenco com poucos jogadores (%d). Recomendo pelo menos 11.\n", newClub.playerCount);
                printf("Continuar mesmo assim? (s/n): ");
                char confirm;
                scanf(" %c", &confirm);
                getchar();
                if (confirm != 's' && confirm != 'S') {
                    continue;
                }
            }
            break;
        }

        int playerIndex = findPlayerIndex(inputName);

        // Jogador NÃO existe → cria simplificado
        if (playerIndex == -1) {
            Player newPlayer;
            strcpy(newPlayer.name, inputName);

            printf("Jogador novo! Número da camisa para %s: ", inputName);
            scanf("%d", &newPlayer.shirtNumber);

            printf("Posição de %s (ex: Atacante, Meia, Zagueiro, Goleiro): ", inputName);
            scanf(" %29[^\n]", newPlayer.position);

            // Dados padrão
            newPlayer.age = 25;
            strcpy(newPlayer.nationality, "Desconhecida");
            strcpy(newPlayer.lastClub, "Nenhum");
            newPlayer.careerGoals = 0;
            strcpy(newPlayer.currentClub, newClub.name);

            // Adiciona ao banco global
            players[playerCount] = newPlayer;
            playerIndex = playerCount;
            playerCount++;

            printf("'%s' (#%d - %s) criado e adicionado ao elenco!\n\n", inputName, newPlayer.shirtNumber, newPlayer.position);
        } else {
            // Jogador já existe
            Player *p = getPlayer(playerIndex);

            // Verifica duplicata no elenco
            int alreadyIn = 0;
            for (int i = 0; i < newClub.playerCount; i++) {
                if (newClub.playerIndexes[i] == playerIndex) {
                    alreadyIn = 1;
                    break;
                }
            }
            if (alreadyIn) {
                printf("'%s' já está no elenco!\n\n", inputName);
                continue;
            }

            strcpy(p->currentClub, newClub.name);
            printf("'%s' (#%d - %s) adicionado ao elenco!\n\n", p->name, p->shirtNumber, p->position);
        }

        // Adiciona ao elenco do clube
        newClub.playerIndexes[newClub.playerCount] = playerIndex;
        newClub.playerCount++;
    }

    clubs[clubCount] = newClub;
    clubCount++;

    saveAllData();

    printf("\nClube '%s' criado com sucesso com %d jogador(es)!\n", newClub.name, newClub.playerCount);
    printf("Pressione ENTER para continuar...");
    getchar(); getchar();
}

void listClubs(void) {
    if (clubCount == 0) {
        printf("\nNenhum clube cadastrado ainda.\n");
        printf("Pressione ENTER para continuar...");
        getchar(); getchar();
        return;
    }

    printf("\n=== LISTA DE CLUBES (%d) ===\n", clubCount);
    for (int i = 0; i < clubCount; i++) {
        printf("\n[%d] %s\n", i + 1, clubs[i].name);
        printf("    Jogadores: %d/%d\n", clubs[i].playerCount, MAX_PLAYERS_PER_CLUB);

        if (clubs[i].playerCount == 0) {
            printf("    (Elenco vazio)\n");
        } else {
            printf("    Elenco:\n");
            for (int j = 0; j < clubs[i].playerCount; j++) {
                Player *p = getPlayer(clubs[i].playerIndexes[j]);
                printf("     • %s #%d (%s)\n", p->name, p->shirtNumber, p->position);
            }
        }
    }

    printf("\nPressione ENTER para continuar...");
    getchar(); getchar();
}

void editClub(void) {
    if (clubCount == 0) {
        printf("\nNenhum clube para editar.\n");
        printf("Pressione ENTER para voltar...");
        getchar(); getchar();
        return;
    }

    listClubs();
    printf("\nDigite o número do clube para editar (ou 0 para voltar): ");
    int choice;
    scanf("%d", &choice);
    if (choice == 0) return;
    choice--;

    if (choice < 0 || choice >= clubCount) {
        printf("Clube inválido!\n");
        getchar(); getchar();
        return;
    }

    Club *c = &clubs[choice];
    int op;

    do {
        printf("\n=== EDITAR CLUBE: %s ===\n", c->name);
        printf("1. Renomear clube\n");
        printf("2. Adicionar jogador\n");
        printf("3. Remover jogador\n");
        printf("4. Remover clube inteiro\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch (op) {
            case 1: {
                printf("Novo nome: ");
                char newName[MAX_CLUB_NAME];
                scanf(" %49[^\n]", newName);

                if (findClubIndex(newName) != -1) {
                    printf("Já existe um clube com esse nome!\n");
                    break;
                }

                for (int i = 0; i < c->playerCount; i++) {
                    Player *p = getPlayer(c->playerIndexes[i]);
                    strcpy(p->currentClub, newName);
                }

                strcpy(c->name, newName);
                saveAllData();
                printf("Clube renomeado!\n");
                break;
            }
            case 2: {
                if (c->playerCount >= MAX_PLAYERS_PER_CLUB) {
                    printf("Elenco cheio!\n");
                    break;
                }

                printf("Nome do jogador: ");
                char name[MAX_NAME];
                scanf(" %49[^\n]", name);

                int idx = findPlayerIndex(name);
                if (idx == -1) {
                    printf("Jogador não encontrado! Cadastre no menu Jogadores ou crie novo clube.\n");
                    break;
                }

                for (int i = 0; i < c->playerCount; i++) {
                    if (c->playerIndexes[i] == idx) {
                        printf("Jogador já está no elenco!\n");
                        break;
                    }
                }

                c->playerIndexes[c->playerCount++] = idx;
                Player *p = getPlayer(idx);
                strcpy(p->currentClub, c->name);
                saveAllData();
                printf("Jogador adicionado!\n");
                break;
            }
            case 3: {
                if (c->playerCount == 0) {
                    printf("Elenco vazio!\n");
                    break;
                }

                printf("Número do jogador para remover: ");
                int rem;
                scanf("%d", &rem);
                rem--;

                if (rem < 0 || rem >= c->playerCount) {
                    printf("Índice inválido!\n");
                    break;
                }

                int playerIdx = c->playerIndexes[rem];
                Player *p = getPlayer(playerIdx);
                strcpy(p->currentClub, "Sem clube");

                for (int i = rem; i < c->playerCount - 1; i++) {
                    c->playerIndexes[i] = c->playerIndexes[i + 1];
                }
                c->playerCount--;

                saveAllData();
                printf("Jogador removido do clube!\n");
                break;
            }
            case 4: {
                printf("Tem certeza que quer REMOVER o clube '%s'? (s/n): ", c->name);
                char confirm;
                scanf(" %c", &confirm);
                getchar();
                if (confirm == 's' || confirm == 'S') {
                    for (int i = 0; i < c->playerCount; i++) {
                        Player *p = getPlayer(c->playerIndexes[i]);
                        strcpy(p->currentClub, "Sem clube");
                    }

                    for (int i = choice; i < clubCount - 1; i++) {
                        clubs[i] = clubs[i + 1];
                    }
                    clubCount--;
                    saveAllData();
                    printf("Clube removido!\n");
                }
                return;
            }
            case 0:
                break;
            default:
                printf("Opção inválida!\n");
        }

        if (op != 0 && op != 4) {
            printf("Pressione ENTER para continuar...");
            getchar(); getchar();
        }
    } while (op != 0);
}

int getClubCount(void) {
    return clubCount;
}

Club* getClub(int index) {
    if (index >= 0 && index < clubCount) {
        return &clubs[index];
    }
    return NULL;
}

int findClubIndex(const char *name) {
    for (int i = 0; i < clubCount; i++) {
        if (strcmp(clubs[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void menuClubes(void) {
    int op;
    do {
        printf("\n--- CLUBES ---\n");
        printf("1. Adicionar clube\n");
        printf("2. Listar clubes\n");
        printf("3. Editar clube\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch (op) {
            case 1: addClub(); break;
            case 2: listClubs(); break;
            case 3: editClub(); break;
            case 0: break;
            default:
                printf("Opção inválida!\n");
                getchar(); getchar();
        }
    } while (op != 0);
}