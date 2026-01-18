#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "club.h"
#include "match.h"
#include "league.h"

extern int isAdm;  // De main.c

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
    int op;

    do {
        clearScreen();

        printf("%s==================================%s\n", ORANGE, RESET);
        printf("%s     SISTEMA DE GESTÃO DE CAMPEONATOS%s\n", ORANGE BOLD, RESET);
        printf("%s==================================%s\n", ORANGE, RESET);
        printf("%s1. Gestão de Equipas %s%s\n", ORANGE, (isAdm ? "(Editar)" : "(Ver apenas)"), RESET);
        printf("%s2. Registo de Jogos %s%s\n", ORANGE, (isAdm ? "(ADM)" : "(Somente visualização)"), RESET);
        printf("%s3. Cálculo da Classificação%s\n", ORANGE, RESET);
        printf("%s4. Relatórios e Estatísticas%s\n", ORANGE, RESET);
        printf("%s5. Gravação e Leitura de Dados%s\n", ORANGE, RESET);
        printf("0. Sair\n");
        printf("%s==================================%s\n", ORANGE, RESET);
        printf("%sEscolha: %s", ORANGE BOLD, RESET);
        scanf("%d", &op);

        clearScreen();

        switch (op) {
            case 1:
                if (isAdm) {
                    printf("%s--- GESTÃO DE EQUIPAS (EDITAR) ---%s\n\n", ORANGE BOLD, RESET);
                    menuEquipas();  // Menu completo com edição
                } else {
                    printf("%s--- VISUALIZAÇÃO DE EQUIPAS ---%s\n\n", ORANGE BOLD, RESET);
                    listClubs();  // Só visualiza
                }
                break;
            case 2:
                if (isAdm) {
                    printf("%s--- REGISTO DE JOGOS ---%s\n\n", ORANGE BOLD, RESET);
                    menuJogos();
                } else {
                    printf("%sAcesso restrito: Apenas ADM pode registar jogos.%s\n", ORANGE, RESET);
                    printf("%sPressione ENTER para continuar...%s", ORANGE, RESET);
                    getchar(); getchar();
                }
                break;
            case 3:
                printf("%s--- CÁLCULO DA CLASSIFICAÇÃO ---%s\n\n", ORANGE BOLD, RESET);
                showLeagueTable();
                printf("\n%sPressione ENTER para continuar...%s", ORANGE, RESET);
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
                printf("%s--- GRAVAÇÃO E LEITURA DE DADOS ---%s\n\n", ORANGE BOLD, RESET);
                printf("%sOs dados são salvos automaticamente em 'manager_data.txt'.%s\n", ORANGE, RESET);
                printf("%sPressione ENTER para continuar...%s", ORANGE, RESET);
                getchar(); getchar();
                break;
            case 0:
                printf("\n%sObrigado por usar o sistema! Até logo! ⚽%s\n", ORANGE, RESET);
                break;
            default:
                printf("%sOpção inválida!%s\n", ORANGE, RESET);
                getchar(); getchar();
        }
    } while (op != 0);
}