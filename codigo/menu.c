#include <stdio.h>               // Biblioteca padrão para entrada/saída (printf, scanf, getchar)
#include <stdlib.h>              // Para system("cls"/"clear") e outras funções do sistema
#include <string.h>              // Para strcmp (comparação de strings)
#include "menu.h"                // O próprio header deste ficheiro (declarações)
#include "club.h"                // Estruturas e funções relacionadas com clubes/equipas
#include "match.h"               // Estruturas e funções relacionadas com partidas/jogos
#include "league.h"              // Função da tabela de classificação
#include "storage.h"             // Funções de salvar/carregar dados

extern int isAdm;                // Variável global definida em main.c (indica se é administrador)

#define ORANGE "\033[38;5;208m"  // Código ANSI para cor laranja no terminal
#define BOLD   "\033[1m"         // Código ANSI para texto em negrito
#define RESET  "\033[0m"         // Código ANSI para resetar a cor/estilo

// Função que limpa a tela do terminal (diferente para Windows e outros sistemas)
void clearScreen() {
#ifdef _WIN32                    // Se estiver a compilar no Windows
    system("cls");               // Comando do Windows para limpar a tela
#else                            // Caso contrário (Linux, macOS, etc.)
    system("clear");             // Comando padrão para limpar a tela
#endif
}

// Função principal do menu do sistema (loop infinito até sair)
void mainMenu(void) {
    char input[50];              // Buffer para ler a entrada do utilizador (permite "Reset" como texto)
    int op;                      // Variável para armazenar a opção convertida para número

    do {                         // Ciclo principal do menu (repete até o utilizador sair)
        clearScreen();           // Limpa o terminal a cada iteração para manter a interface limpa

        // Cabeçalho do menu com cor laranja
        printf("%s==================================%s\n", ORANGE, RESET);
        printf("%s            Fut Stats     %s\n", ORANGE BOLD, RESET);
        printf("%s==================================%s\n", ORANGE, RESET);

        // Lista as opções do menu (com indicação se é restrito ou editável)
        printf("%s1. Gestão de Equipas %s%s\n", ORANGE, (isAdm ? "(Editar)" : "(Ver apenas)"), RESET);
        printf("%s2. Registo de Jogos %s%s\n", ORANGE, (isAdm ? "(ADM)" : "(Somente visualização)"), RESET);
        printf("%s3. Cálculo da Classificação%s\n", ORANGE, RESET);
        printf("%s4. Relatórios e Estatísticas%s\n", ORANGE, RESET);
        printf("%s5. Gravação e Leitura de Dados%s\n", ORANGE, RESET);
        printf("0. Sair\n");
        printf("%s==================================%s\n", ORANGE, RESET);

        // Pede entrada ao utilizador (número ou texto como "Reset")
        printf("%sDigite a opção ou 'Reset' (ADM): %s", ORANGE BOLD, RESET);
        scanf(" %49[^\n]", input);  // Lê até ao Enter (permite espaços e texto completo)

        // Verifica se o utilizador digitou "Reset" (apenas ADM pode resetar tudo)
        if (strcmp(input, "Reset") == 0) {
            if (isAdm) {             // Só permite se for administrador
                playerCount = 0;     // Apaga todos os jogadores
                clubCount = 0;       // Apaga todos os clubes
                matchCount = 0;      // Apaga todos os jogos/partidas
                saveAllData();       // Salva o estado vazio no ficheiro
                printf("\n%sDADOS RESETADOS COM SUCESSO!%s\n", ORANGE BOLD, RESET);
            } else {
                printf("%sAcesso negado: apenas ADM pode resetar.%s\n", ORANGE, RESET);
            }
            printf("%sPressione ENTER para continuar...%s", ORANGE, RESET);
            getchar(); getchar();    // Espera ENTER para prosseguir
            continue;                // Volta ao início do loop (sem processar como número)
        }

        // Converte a entrada para número inteiro (se for número)
        op = atoi(input);

        // Processa a opção escolhida
        switch (op) {
            case 1:
                if (isAdm) {
                    menuEquipas();   // Chama menu completo de edição (apenas para ADM)
                } else {
                    viewClubs();     // Apenas visualização (para usuário normal)
                }
                break;

            case 2:
                if (isAdm) {
                    menuJogos();     // Acesso completo a registo de jogos (apenas ADM)
                } else {
                    printf("%sAcesso restrito.%s\n", ORANGE, RESET);
                    getchar(); getchar();  // Espera ENTER para voltar ao menu
                }
                break;

            case 3:
                showLeagueTable();   // Mostra a tabela de classificação (disponível para todos)
                printf("\n%sPressione ENTER...%s", ORANGE, RESET);
                getchar(); getchar();      // Espera ENTER
                break;

            case 4:
                // Sub-menu de relatórios e estatísticas
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
                // Informação sobre salvamento automático
                printf("%sDados salvos automaticamente.%s\n", ORANGE, RESET);
                getchar(); getchar();      // Espera ENTER
                break;

            case 0:
                // Mensagem de saída
                printf("\n%sAté logo! ⚽%s\n", ORANGE, RESET);
                break;

            default:
                // Caso a entrada não seja um número válido ou opção conhecida
                printf("%sOpção inválida!%s\n", ORANGE, RESET);
                getchar(); getchar();
        }
    } while (op != 0);  // Sai do loop apenas quando o utilizador escolhe 0
}