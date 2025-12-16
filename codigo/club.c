#include <stdio.h>
#include <string.h>
#include "club.h"

Clube clubes[MAX_CLUBES];

void inicializarClubes() {
    for (int i = 0; i < MAX_CLUBES; i++) {
        clubes[i].ativo = 0;
        clubes[i].id = i;
    }
}

void criarClube() {
    for (int i = 0; i < MAX_CLUBES; i++) {
        if (!clubes[i].ativo) {
            printf("Nome do clube: ");
            scanf(" %[^\n]", clubes[i].nome);
            
            clubes[i].ativo = 1;

            printf("Clube criado com sucesso!\n");
            return;
        }
    }
    printf("Limite máximo de clubes atingido!\n");
}

void listarClubes() {
    printf("\n--- Lista de Clubes ---\n");
    for (int i = 0; i < MAX_CLUBES; i++) {
        if (clubes[i].ativo)
            printf("%d - %s\n", clubes[i].id, clubes[i].nome);
    }
}

void editarClube() {
    int id = escolherClube();
    if (id == -1) return;

    printf("Novo nome: ");
    scanf(" %[^\n]", clubes[id].nome);

    printf("Clube editado!\n");
}

void removerClube() {
    int id = escolherClube();
    if (id == -1) return;

    clubes[id].ativo = 0;

    printf("Clube removido!\n");
}

int escolherClube() {
    listarClubes();
    printf("Escolha o ID do clube: ");
    int id;
    scanf("%d", &id);

    if (id < 0 || id >= MAX_CLUBES || !clubes[id].ativo) {
        printf("Clube inválido!\n");
        return -1;
    }
    return id;
}
