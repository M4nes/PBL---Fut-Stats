#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "menu.h"
#include "storage.h"

#ifdef _WIN32
#include <windows.h>
#endif

// Cores ANSI
#define ORANGE "\033[38;5;208m"
#define BOLD   "\033[1m"
#define RESET  "\033[0m"

// Variável global para saber se é ADM
int isAdm = 0;

#define ADM_USERNAME "admin"
#define ADM_PASSWORD "admin123"
#define USER_USERNAME "user"
#define USER_PASSWORD "user123"

void login() {
    char username[50];
    char password[50];

    clearScreen();  // Limpa tela antes do login

    printf("%s=== SISTEMA DE LOGIN ===%s\n", ORANGE BOLD, RESET);
    printf("Username: ");
    scanf(" %49[^\n]", username);

    printf("Password: ");
    scanf(" %49[^\n]", password);

    if (strcmp(username, ADM_USERNAME) == 0 && strcmp(password, ADM_PASSWORD) == 0) {
        isAdm = 1;
        printf("\n%sLogin ADM bem-sucedido! Acesso total liberado.%s\n", ORANGE, RESET);
    } else if (strcmp(username, USER_USERNAME) == 0 && strcmp(password, USER_PASSWORD) == 0) {
        isAdm = 0;
        printf("\n%sLogin Usuário bem-sucedido! Acesso limitado.%s\n", ORANGE, RESET);
    } else {
        printf("\n%sLogin inválido! Entrando como Usuário (acesso limitado).%s\n", ORANGE, RESET);
        isAdm = 0;
    }

    printf("%sPressione ENTER para continuar...%s", ORANGE, RESET);
    getchar(); getchar();
}

int main() {
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif
    srand(time(NULL));

    login();

    loadAllData();
    mainMenu();
    saveAllData();

    return 0;
}