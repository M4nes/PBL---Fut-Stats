#include <stdio.h>
#include <string.h>
#include "player.h"


void createPlayer(Player *p) {
printf("Digite o nome do jogador: ");
fgets(p->name, MAX_NAME, stdin);
p->name[strcspn(p->name, "\n")] = '\0';


printf("Idade: ");
scanf("%d", &p->age);
getchar();


printf("Posição: ");
fgets(p->position, 20, stdin);
p->position[strcspn(p->position, "\n")] = '\0';
}


void printPlayer(Player p) {
printf("Nome: %s | Idade: %d | Posição: %s\n", p.name, p.age, p.position);
}