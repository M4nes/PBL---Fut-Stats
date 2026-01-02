#include <stdio.h>
#include <string.h>
#include "player.h"
#include "storage.h"  // Para salvar após edição

Player players[MAX_PLAYERS];
int playerCount = 0;

void addPlayer(void) {
    if (playerCount >= MAX_PLAYERS) {
        printf("\nLimite de jogadores atingido (%d)!\n", MAX_PLAYERS);
        return;
    }

    Player p;
    
    printf("\n=== ADICIONAR JOGADOR ===\n");
    printf("Nome: ");
    scanf(" %49[^\n]", p.name);

    printf("Idade: ");
    scanf("%d", &p.age);

    printf("Nacionalidade: ");
    scanf(" %49[^\n]", p.nationality);

    printf("Posição (ex: Atacante, Meia, Zagueiro, Goleiro): ");
    scanf(" %29[^\n]", p.position);

    printf("Último clube (ou 'Nenhum' se não teve): ");
    scanf(" %49[^\n]", p.lastClub);

    strcpy(p.currentClub, "Sem clube");
    p.careerGoals = 0;

    players[playerCount] = p;
    playerCount++;

    saveAllData();  // Salva automaticamente

    printf("\nJogador '%s' adicionado com sucesso!\n", p.name);
    printf("Pressione ENTER para continuar...");
    getchar(); getchar();
}

void listPlayers(void) {
    if (playerCount == 0) {
        printf("\nNenhum jogador cadastrado ainda.\n");
        printf("Pressione ENTER para voltar...");
        getchar(); getchar();
        return;
    }

    printf("\n=== LISTA DE JOGADORES (%d) ===\n", playerCount);
    for (int i = 0; i < playerCount; i++) {
        printf("\n[%d] %s\n", i + 1, players[i].name);
        printf("    Idade: %d | Nacionalidade: %s\n", players[i].age, players[i].nationality);
        printf("    Posição: %s\n", players[i].position);
        printf("    Último clube: %s | Clube atual: %s\n", players[i].lastClub, players[i].currentClub);
        printf("    Gols na carreira: %d\n", players[i].careerGoals);
    }

    printf("\nPressione ENTER para voltar...");
    getchar(); getchar();
}

void editPlayer(void) {
    if (playerCount == 0) {
        printf("\nNenhum jogador para editar.\n");
        printf("Pressione ENTER para voltar...");
        getchar(); getchar();
        return;
    }

    listPlayers();

    printf("\nDigite o número do jogador para editar (ou 0 para voltar): ");
    int choice;
    scanf("%d", &choice);
    if (choice == 0) return;
    choice--;

    if (choice < 0 || choice >= playerCount) {
        printf("Jogador inválido!\n");
        getchar(); getchar();
        return;
    }

    Player *p = &players[choice];

    int op;
    do {
        printf("\n=== EDITAR JOGADOR: %s ===\n", p->name);
        printf("1. Alterar nome\n");
        printf("2. Alterar idade\n");
        printf("3. Alterar nacionalidade\n");
        printf("4. Alterar posição\n");
        printf("5. Alterar último clube\n");
        printf("6. Adicionar gols na carreira\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                printf("Novo nome: ");
                scanf(" %49[^\n]", p->name);
                break;
            case 2:
                printf("Nova idade: ");
                scanf("%d", &p->age);
                break;
            case 3:
                printf("Nova nacionalidade: ");
                scanf(" %49[^\n]", p->nationality);
                break;
            case 4:
                printf("Nova posição: ");
                scanf(" %29[^\n]", p->position);
                break;
            case 5:
                printf("Novo último clube (ou 'Nenhum'): ");
                scanf(" %49[^\n]", p->lastClub);
                break;
            case 6:
                printf("Gols atuais: %d\n", p->careerGoals);
                printf("Quantos gols adicionar? ");
                int gols;
                scanf("%d", &gols);
                if (gols >= 0) {
                    p->careerGoals += gols;
                    printf("Agora %s tem %d gols na carreira!\n", p->name, p->careerGoals);
                } else {
                    printf("Valor inválido!\n");
                }
                break;
            case 0:
                break;
            default:
                printf("Opção inválida!\n");
        }

        if (op != 0) {
            saveAllData();  // Salva a cada mudança
            printf("Alteração salva!\n");
            printf("Pressione ENTER para continuar...");
            getchar(); getchar();
        }
    } while (op != 0);

    printf("Edição concluída!\n");
}

int findPlayerIndex(const char *name) {
    for (int i = 0; i < playerCount; i++) {
        if (strcmp(players[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

Player* getPlayer(int index) {
    if (index >= 0 && index < playerCount) {
        return &players[index];
    }
    return NULL;
}

int getPlayerCount(void) {
    return playerCount;
}

void menuJogadores(void) {
    int op;
    do {
        printf("\n--- JOGADORES ---\n");
        printf("1. Adicionar jogador\n");
        printf("2. Listar jogadores\n");
        printf("3. Editar jogador\n");   // NOVA OPÇÃO
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                addPlayer();
                break;
            case 2:
                listPlayers();
                break;
            case 3:
                editPlayer();   // Nova função
                break;
            case 0:
                break;
            default:
                printf("Opção inválida!\n");
                getchar(); getchar();
        }
    } while (op != 0);
}