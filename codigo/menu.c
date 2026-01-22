#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "club.h"
#include "match.h"
#include "league.h"
#include "storage.h"

extern int isAdm;

#define ORANGE "\033[38;5;208m"
#define BOLD   "\033[1m"
#define RESET  "\033[0m"

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


void mainMenu(void) {
    char input[50];
    int op;

    do {
        clearScreen();

        printf("%s==================================%s\n", ORANGE, RESET);
        printf("%s            Fut Stats     %s\n", ORANGE BOLD, RESET);
        printf("%s==================================%s\n", ORANGE, RESET);
        printf("%s1. Gestão de Equipas %s%s\n", ORANGE, (isAdm ? "(Editar)" : "(Ver apenas)"), RESET);
        printf("%s2. Registo de Jogos %s%s\n", ORANGE, (isAdm ? "(ADM)" : "(Somente visualização)"), RESET);
        printf("%s3. Cálculo da Classificação%s\n", ORANGE, RESET);
        printf("%s4. Relatórios e Estatísticas%s\n", ORANGE, RESET);
        printf("%s5. Gravação e Leitura de Dados%s\n", ORANGE, RESET);
        printf("0. Sair\n");
        printf("%s==================================%s\n", ORANGE, RESET);
        printf("%sDigite a opção ou 'Reset' (ADM): %s", ORANGE BOLD, RESET);
        scanf(" %49[^\n]", input);

        // Verifica se digitou "Reset" (só ADM)
        if (strcmp(input, "Reset") == 0) {
            if (isAdm) {
                playerCount = 0;
                clubCount = 0;
                matchCount = 0;
                saveAllData();
                printf("\n%sDADOS RESETADOS COM SUCESSO!%s\n", ORANGE BOLD, RESET);
                printf("%sPressione ENTER para continuar...%s", ORANGE, RESET);
                getchar(); getchar();
            } else {
                printf("%sAcesso negado: apenas ADM pode resetar.%s\n", ORANGE, RESET);
                printf("%sPressione ENTER...%s", ORANGE, RESET);
                getchar(); getchar();
            }
            continue;
        }

        op = atoi(input);

        switch (op) {
            case 1:
                if (isAdm) menuEquipas();
                else viewClubs();
                break;
            case 2:
                if (isAdm) menuJogos();
                else {
                    printf("%sAcesso restrito.%s\n", ORANGE, RESET);
                    getchar(); getchar();
                }
                break;
            case 3:
                showLeagueTable();
                printf("\n%sPressione ENTER...%s", ORANGE, RESET);
                getchar(); getchar();
                break;
            case 4:
                printf("%s--- RELATÓRIOS E ESTATÍSTICAS ---%s\n\n", ORANGE BOLD, RESET);
                printf("1. Classificação\n");
                printf("2. Histórico de jogos\n");
                printf("Escolha: ");
                int rel;
                scanf("%d", &rel);
                if (rel == 1) showLeagueTable();
                else if (rel == 2) listMatchHistory();
                printf("\n%sPressione ENTER...%s", ORANGE, RESET);
                getchar(); getchar();
                break;
            case 5:
                printf("%sDados salvos automaticamente.%s\n", ORANGE, RESET);
                getchar(); getchar();
                break;
            case 0:
                printf("\n%sAté logo! ⚽%s\n", ORANGE, RESET);
                break;
            default:
                printf("%sOpção inválida!%s\n", ORANGE, RESET);
                getchar(); getchar();
        }
    } while (op != 0);
}