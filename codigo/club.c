#include <stdio.h>
#include <string.h>
#include "club.h"

#define MAX_CLUBS 50

Club clubs[MAX_CLUBS];
int clubCount = 0;

void addClub(){
    if(clubCount >= MAX_CLUBS){
        printf("Limite de clubes atingido!\n");
        return;
    }

    if(getPlayerCount() == 0){
        printf("Adicione jogadores primeiro antes de criar clubes!\n");
        return;
    }

    Club c;

    printf("Nome do clube: ");
    scanf(" %[^\n]", c.name);

    c.playerCount = 0;

    int option;
    do {
        printf("Digite o nome do jogador para adicionar (ou '0' para sair): ");
        char name[50];
        scanf(" %[^\n]", name);

        if(strcmp(name, "0") == 0) break;

        int index = findPlayerIndex(name);

        if(index == -1){
            printf("Jogador nao encontrado! Adicione ele primeiro no menu jogadores.\n");
        } else {
            c.playerIndexes[c.playerCount++] = index;
            printf("Jogador adicionado ao clube!\n");
        }

    } while(1);

    clubs[clubCount++] = c;

    printf("Clube criado com sucesso!\n");
}

void listClubs(){
    if(clubCount == 0){
        printf("Nenhum clube criado ainda.\n");
        return;
    }

    for(int i = 0; i < clubCount; i++){
        printf("\n--- Clube %d ---\n", i+1);
        printf("Nome: %s\n", clubs[i].name);
        printf("Jogadores:\n");

        for(int j = 0; j < clubs[i].playerCount; j++){
            Player p = getPlayer(clubs[i].playerIndexes[j]);
            printf("- %s\n", p.name);
        }
    }
}

void editClub(){
    if(clubCount == 0){
        printf("Nenhum clube para editar.\n");
        return;
    }

    listClubs();

    int choice;
    printf("\nEscolha o numero do clube: ");
    scanf("%d", &choice);
    choice--;

    if(choice < 0 || choice >= clubCount){
        printf("Clube invalido.\n");
        return;
    }

    int op;
    do {
        printf("\nEditar Clube %s\n", clubs[choice].name);
        printf("1 - Renomear clube\n");
        printf("2 - Remover clube\n");
        printf("3 - Adicionar jogador\n");
        printf("4 - Remover jogador\n");
        printf("0 - Voltar\n");
        printf("Opcao: ");
        scanf("%d", &op);

        if(op == 1){
            printf("Novo nome: ");
            scanf(" %[^\n]", clubs[choice].name);
        }
        else if(op == 2){
            for(int i = choice; i < clubCount-1; i++){
                clubs[i] = clubs[i+1];
            }
            clubCount--;
            printf("Clube removido!\n");
            return;
        }
    } while(op != 0);
}
