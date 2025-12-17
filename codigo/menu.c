#include <stdio.h>
#include "menu.h"


void showMainMenu() {
printf("\n===== FOOTBALL MANAGER =====\n");
printf("1 - Criar Clube\n");
printf("2 - Adicionar Jogador\n");
printf("3 - Mostrar Clube\n");
printf("0 - Sair\n");
printf("Escolha: ");
}


void handleMainMenu(Club *club) {
int option;


do {
showMainMenu();
scanf("%d", &option);
getchar();


switch(option) {
case 1:
createClub(club);
break;
case 2:
addPlayerToClub(club);
break;
case 3:
printClub(*club);
break;
case 0:
printf("Saindo...\n");
break;
default:
printf("Opção inválida!\n");
}


} while(option != 0);
}