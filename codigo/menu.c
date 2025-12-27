#include <stdio.h>
#include "menu.h"
#include "player.h"
#include "club.h"

void mainMenu(){
    int op;

    do{
        printf("\n===== FUT STATS =====\n");
        printf("1. Clubes\n");
        printf("2. Jogadores\n");
        printf("3. Jogos (iremos fazer depois)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);

        if(op == 1){
            int c;
            do {
                printf("\n--- CLUBES ---\n");
                printf("1. Adicionar clube\n");
                printf("2. Mostrar clubes\n");
                printf("3. Editar clube\n");
                printf("0. Voltar\n");
                printf("Escolha: ");
                scanf("%d", &c);

                if(c == 1) addClub();
                else if(c == 2) listClubs();
                else if(c == 3) editClub();

            } while(c != 0);
        }

        else if(op == 2){
            int j;
            do {
                printf("\n--- JOGADORES ---\n");
                printf("1. Adicionar jogador\n");
                printf("2. Mostrar jogadores\n");
                printf("0. Voltar\n");
                printf("Escolha: ");
                scanf("%d", &j);

                if(j == 1) addPlayer();
                else if(j == 2) listPlayers();

            } while(j != 0);
        }

    } while(op != 0);
}
