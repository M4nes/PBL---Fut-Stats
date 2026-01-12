#include <stdio.h>
#include "menu.h"
#include "club.h"
#include "match.h"
#include "league.h"

void mainMenu(void) {
    int op;

    do {
        printf("\n==================================\n");
        printf("     SISTEMA DE GESTÃO DE CAMPEONATOS\n");
        printf("==================================\n");
        printf("1. Gestão de Equipas\n");
        printf("2. Registo de Jogos\n");
        printf("3. Cálculo da Classificação\n");
        printf("4. Relatórios e Estatísticas\n");
        printf("5. Gravação e Leitura de Dados\n");
        printf("0. Sair\n");
        printf("==================================\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                menuEquipas();
                break;
            case 2:
                menuJogos();
                break;
            case 3:
                showLeagueTable();
                printf("\nPressione ENTER para continuar...");
                getchar(); getchar();
                break;
            case 4:
                printf("\n--- RELATÓRIOS E ESTATÍSTICAS ---\n");
                printf("1. Classificação\n");
                printf("2. Histórico de jogos\n");
                printf("Escolha: ");
                int rel;
                scanf("%d", &rel);
                if (rel == 1) showLeagueTable();
                else if (rel == 2) listMatchHistory();
                printf("\nPressione ENTER para continuar...");
                getchar(); getchar();
                break;
            case 5:
                printf("\nOs dados são salvos automaticamente em 'manager_data.txt'.\n");
                printf("Pressione ENTER para continuar...");
                getchar(); getchar();
                break;
            case 0:
                printf("\nObrigado por usar o sistema! Até logo! ⚽\n");
                break;
            default:
                printf("Opção inválida!\n");
                getchar(); getchar();
        }
    } while (op != 0);
}