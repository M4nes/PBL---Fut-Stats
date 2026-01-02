#include <stdio.h>
#include "menu.h"
#include "storage.h"

int main() {
    printf("Carregando dados salvos...\n");
    loadAllData();                // Carrega jogadores, clubes e partidas do arquivo

    mainMenu();

    printf("Salvando dados...\n");
    saveAllData();                // Salva tudo ao sair

    return 0;
}