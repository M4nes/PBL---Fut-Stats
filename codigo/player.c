#include <stdio.h>
#include <string.h>
#include "player.h"

#define MAX_PLAYERS 100

Player players[MAX_PLAYERS];
int playerCount = 0;

void addPlayer() {
    if(playerCount >= MAX_PLAYERS) {
        printf("Limite de jogadores atingido!\n");
        return;
    }

    Player p;

    printf("Nome: ");
    scanf(" %[^\n]", p.name);

    printf("Idade: ");
    scanf("%d", &p.age);

    printf("Nacionalidade: ");
    scanf(" %[^\n]", p.nationality);

    printf("Posicao: ");
    scanf(" %[^\n]", p.position);

    printf("Dia de nascimento: ");
    scanf("%d", &p.birthDay);

    printf("Mes de nascimento: ");
    scanf("%d", &p.birthMonth);

    printf("Ano de nascimento: ");
    scanf("%d", &p.birthYear);

    printf("Teve ultimo clube? (1 = sim / 0 = nao): ");
    int op;
    scanf("%d", &op);

    if(op == 1){
        printf("Ultimo clube: ");
        scanf(" %[^\n]", p.lastClub);
    } else {
        strcpy(p.lastClub, "Nenhum");
    }

    strcpy(p.currentClub, "Sem clube");
    p.careerGoals = 0;

    players[playerCount++] = p;

    printf("Jogador adicionado com sucesso!\n");
}

void listPlayers() {
    if(playerCount == 0){
        printf("Nenhum jogador cadastrado ainda.\n");
        return;
    }

    for(int i = 0; i < playerCount; i++){
        printf("\n--- Jogador %d ---\n", i+1);
        printf("Nome: %s\n", players[i].name);
        printf("Idade: %d\n", players[i].age);
        printf("Nacionalidade: %s\n", players[i].nationality);
        printf("Posicao: %s\n", players[i].position);
        printf("Nascimento: %02d/%02d/%d\n", players[i].birthDay, players[i].birthMonth, players[i].birthYear);
        printf("Ultimo clube: %s\n", players[i].lastClub);
        printf("Clube atual: %s\n", players[i].currentClub);
        printf("Gols na carreira: %d\n", players[i].careerGoals);
    }
}

int findPlayerIndex(char name[]) {
    for(int i = 0; i < playerCount; i++){
        if(strcmp(players[i].name, name) == 0)
            return i;
    }
    return -1;
}

Player getPlayer(int index){
    return players[index];
}

int getPlayerCount(){
    return playerCount;
}
