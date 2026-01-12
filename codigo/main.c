#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "menu.h"
#include "storage.h"

int main() {
    srand(time(NULL));  // Inicializa números aleatórios

    loadAllData();
    mainMenu();
    saveAllData();

    return 0;
}