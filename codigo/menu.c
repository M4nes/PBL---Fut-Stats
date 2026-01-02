#include <stdio.h>
#include "menu.h"
#include "player.h"
#include "club.h"
#include "match.h"

void mainMenu(void) {
    int op;

    do {
        printf("\n");
        printf("==================================\n");
        printf("          FUT STATS\n");
        printf("==================================\n");
        printf("1. Jogadores     (%d cadastrados)\n", getPlayerCount());
        printf("2. Clubes        (%d cadastrados)\n", getClubCount());
        printf("3. Partidas      (%d jogadas)\n", matchCount);
        printf("0. Sair\n");
        printf("==================================\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                menuJogadores();
                break;
            case 2:
                menuClubes();
                break;
            case 3:
                menuPartidas();
                break;
            case 0:
                printf("\nObrigado por jogar Fut Stats! Até a próxima! ⚽\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
                printf("Pressione ENTER para continuar...");
                getchar(); getchar();
        }
    } while (op != 0);
}