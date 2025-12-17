#include <stdio.h>
#include <string.h>
#include "club.h"


void createClub(Club *c) {
printf("Digite o nome do clube: ");
fgets(c->name, MAX_CLUB_NAME, stdin);
c->name[strcspn(c->name, "\n")] = '\0';
c->playerCount = 0;
}


void addPlayerToClub(Club *c) {
if (c->playerCount >= MAX_PLAYERS) {
printf("Time cheio! Não é possível adicionar mais jogadores.\n");
return;
}


printf("\n=== Adicionar Jogador ao Clube %s ===\n", c->name);
createPlayer(&c->players[c->playerCount]);
c->playerCount++;
}


void printClub(Club c) {
printf("\n=== Clube: %s ===\n", c.name);
printf("Jogadores (%d):\n", c.playerCount);


for(int i = 0; i < c.playerCount; i++) {
printPlayer(c.players[i]);
}
}