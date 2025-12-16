#include <stdio.h>
#include <string.h>
#include "player.h"
#include "club.h"

Jogador jogadores[MAX_JOGADORES];

void inicializarJogadores() {
    for (int i = 0; i < MAX_JOGADORES; i++) {
        jogadores[i].ativo = 0;
        jogadores[i].id = i;
    }
}

void adicionarJogador() {
    int clubeId = escolherClube();
    if (clubeId == -1) return;

    for (int i = 0; i < MAX_JOGADORES; i++) {
        if (!jogadores[i].ativo) {
            printf("Nome do jogador: ");
            scanf(" %[^\n]", jogadores[i].nome);

            printf("Idade: ");
            scanf("%d", &jogadores[i].idade);

            jogadores[i].clubeId = clubeId;
            jogadores[i].ativo = 1;

            printf("Jogador adicionado!\n");
            return;
        }
    }

    printf("Limite de jogadores atingido!\n");
}

void listarJogadoresPorClube() {
    int clubeId = escolherClube();
    if (clubeId == -1) return;

    printf("\nJogadores do clube %s:\n", clubes[clubeId].nome);
    for (int i = 0; i < MAX_JOGADORES; i++) {
        if (jogadores[i].ativo && jogadores[i].clubeId == clubeId) {
            printf("%d - %s (%d anos)\n", jogadores[i].id, jogadores[i].nome, jogadores[i].idade);
        }
    }
}

void editarJogador() {
    int id;
    printf("ID do jogador: ");
    scanf("%d", &id);

    if (id < 0 || id >= MAX_JOGADORES || !jogadores[id].ativo) {
        printf("Jogador inválido!\n");
        return;
    }

    printf("Novo nome: ");
    scanf(" %[^\n]", jogadores[id].nome);

    printf("Nova idade: ");
    scanf("%d", &jogadores[id].idade);

    printf("Jogador editado!\n");
}

void removerJogador() {
    int id;
    printf("ID do jogador para remover: ");
    scanf("%d", &id);

    if (id < 0 || id >= MAX_JOGADORES || !jogadores[id].ativo) {
        printf("Jogador inválido!\n");
        return;
    }

    jogadores[id].ativo = 0;
    printf("Jogador removido!\n");
}
