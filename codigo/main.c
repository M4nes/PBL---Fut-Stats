#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "menu.h"
#include "storage.h"

#ifdef _WIN32
#include <windows.h>
#endif

#define ADM_USERNAME "admin"
#define ADM_PASSWORD "admin123"

#define USER_USERNAME "user"
#define USER_PASSWORD "user123"

int isAdm = 0;

void login() {
    char username[50];
    char password[50];

    printf("\n=== SISTEMA DE LOGIN ===\n");
    printf("Username: ");
    scanf(" %49[^\n]", username);

    printf("Password: ");
    scanf(" %49[^\n]", password);

    if (strcmp(username, ADM_USERNAME) == 0 && strcmp(password, ADM_PASSWORD) == 0) {
        isAdm = 1;
        printf("\nLogin ADM bem-sucedido!\n");
    } else if (strcmp(username, USER_USERNAME) == 0 && strcmp(password, USER_PASSWORD) == 0) {
        isAdm = 0;
        printf("\nLogin Usuário bem-sucedido!\n");
    } else {
        printf("\nLogin inválido! Usando modo Usuário.\n");
        isAdm = 0;
    }
    getchar(); getchar();
}

int main() {
    srand(time(NULL));  

    login();  

    loadAllData();
    mainMenu();
    saveAllData();

    return 0;
}