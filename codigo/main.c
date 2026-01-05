#include <stdio.h>
#include "menu.h"
#include "storage.h"

//typeof struct cria "tipos personalizados" como classes simples

int main() {
    printf("Carregando dados salvos...\n");
    loadAllData();                // Carrega jogadores, clubes e partidas do arquivo

    mainMenu();                   // Chama o menu principal, onde escolhe o que fazer (jogadores, clubes, partidas).

    printf("Salvando dados...\n");
    saveAllData();                // Salva tudo ao sair

    return 0;
}