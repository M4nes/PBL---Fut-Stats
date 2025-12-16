#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "club.h"
#include "player.h"

void iniciarSistema() {
    inicializarClubes();
    inicializarJogadores();
    menuPrincipal();
}

void menuPrincipal() {
    int opcao;

    do {
        printf("\n==== FOOTBALL MANAGER ====\n");
        printf("1. Gerenciar Clubes\n");
        printf("2. Gerenciar Jogadores\n");
        printf("3. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: menuClubes(); break;
            case 2: menuJogadores(); break;
            case 3: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }

    } while(opcao != 3);
}

void menuClubes() {
    int opcao;
    do {
        printf("\n--- MENU DE CLUBES ---\n");
        printf("1. Criar clube\n");
        printf("2. Listar clubes\n");
        printf("3. Editar clube\n");
        printf("4. Remover clube\n");
        printf("5. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: criarClube(); break;
            case 2: listarClubes(); break;
            case 3: editarClube(); break;
            case 4: removerClube(); break;
            case 5: break;
            default: printf("Opção inválida!\n");
        }
    } while(opcao != 5);
}

void menuJogadores() {
    int opcao;

    do {
        printf("\n--- MENU DE JOGADORES ---\n");
        printf("1. Adicionar jogador a um clube\n");
        printf("2. Listar jogadores de um clube\n");
        printf("3. Remover jogador de um clube\n");
        printf("4. Editar jogador\n");
        printf("5. Voltar\n");

        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: adicionarJogador(); break;
            case 2: listarJogadoresPorClube(); break;
            case 3: removerJogador(); break;
            case 4: editarJogador(); break;
            case 5: break;
            default: printf("Opção inválida!\n");
        }

    } while(opcao != 5);
}
