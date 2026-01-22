#include <stdio.h>               // Biblioteca padrão para entrada/saída (printf, scanf, etc.)
#include <stdlib.h>              // Para funções como srand(), rand(), exit(), system(), etc.
#include <time.h>                // Para usar time() e inicializar números aleatórios com srand(time(NULL))
#include <string.h>              // Para funções de comparação de strings (strcmp)
#include "menu.h"                // Header com declaração da função mainMenu()
#include "storage.h"             // Header com declarações de loadAllData() e saveAllData()

#ifdef _WIN32                    // Verifica se estamos a compilar no Windows
#include <windows.h>             // Necessário para SetConsoleOutputCP e SetConsoleCP (suporte a UTF-8)
#endif

#define ADM_USERNAME "admin"     // Nome de utilizador do administrador
#define ADM_PASSWORD "admin123"  // Senha do administrador

#define USER_USERNAME "user"     // Nome de utilizador normal
#define USER_PASSWORD "user123"  // Senha do utilizador normal

int isAdm = 0;                   // Variável global: 1 = logado como ADM, 0 = logado como usuário normal

// Função de autenticação/login
void login() {
    char username[50];           // Buffer para armazenar o nome de usuário digitado
    char password[50];           // Buffer para armazenar a senha digitada

    printf("\n=== SISTEMA DE LOGIN ===\n");  // Cabeçalho do login
    printf("Username: ");
    scanf(" %49[^\n]", username);  // Lê o username (permite espaços)

    printf("Password: ");
    scanf(" %49[^\n]", password);  // Lê a senha (permite espaços)

    // Verifica se as credenciais são do administrador
    if (strcmp(username, ADM_USERNAME) == 0 && strcmp(password, ADM_PASSWORD) == 0) {
        isAdm = 1;               // Define como administrador
        printf("\nLogin ADM bem-sucedido!\n");
    } 
    // Verifica se as credenciais são de usuário normal
    else if (strcmp(username, USER_USERNAME) == 0 && strcmp(password, USER_PASSWORD) == 0) {
        isAdm = 0;               // Define como usuário normal
        printf("\nLogin Usuário bem-sucedido!\n");
    } 
    // Caso inválido: entra como usuário normal por padrão
    else {
        printf("\nLogin inválido! Usando modo Usuário.\n");
        isAdm = 0;
    }

    getchar(); getchar();        // Consome o ENTER restante e espera mais um ENTER para continuar
}

// Função principal do programa
int main() {
#ifdef _WIN32                    // Apenas no Windows: força o terminal a usar UTF-8 para acentos corretos
    SetConsoleOutputCP(CP_UTF8); // Define saída do console como UTF-8
    SetConsoleCP(CP_UTF8);       // Define entrada do console como UTF-8
#endif

    srand(time(NULL));           // Inicializa gerador de números aleatórios com base no tempo atual

    login();                     // Executa o processo de login no início do programa

    loadAllData();               // Carrega todos os dados salvos anteriormente (jogadores, clubes, jogos)

    mainMenu();                  // Entra no menu principal do sistema (loop infinito até sair)

    saveAllData();               // Ao sair do programa, salva todos os dados atuais no ficheiro

    return 0;                    // Termina o programa com código de sucesso
}