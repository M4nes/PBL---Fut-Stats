#ifndef MENU_H              // Proteção contra inclusão múltipla: evita erros se o header for incluído mais de uma vez no mesmo ficheiro
#define MENU_H               // Define o símbolo MENU_H para marcar que este header já foi incluído

// Declaração da função principal do menu (definida em menu.c)
void mainMenu(void);

// Declaração da função que limpa a tela do terminal (definida em menu.c)
void clearScreen(void);

// Declaração da função que inicia um torneio automático com 8 equipas (definida em match.c ou menu.c)
void startTournament(void);

#endif                       // Fim da proteção contra inclusão múltipla