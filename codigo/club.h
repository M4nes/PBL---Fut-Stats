#ifndef CLUB_H                  // Proteção contra inclusão múltipla: evita erros se o header for incluído mais de uma vez no mesmo ficheiro
#define CLUB_H                   // Define o símbolo CLUB_H para marcar que este header já foi incluído

#include "player.h"              // Inclui o header de jogadores (necessário para usar struct Player e funções relacionadas)

#define MAX_CLUBS 50             // Número máximo de clubes/equipas que o sistema pode armazenar
#define MAX_PLAYERS_PER_CLUB 30  // Número máximo de jogadores que uma equipa pode ter no elenco
#define MAX_CLUB_NAME 50         // Tamanho máximo do nome de um clube (incluindo o '\0' final)

// Definição da estrutura que representa um clube/equipa
typedef struct {
    char name[MAX_CLUB_NAME];               // Nome completo do clube (ex: "FC Porto", "Sporting CP")
    int playerIndexes[MAX_PLAYERS_PER_CLUB]; // Array com os índices dos jogadores no array global 'players'
    int playerCount;                        // Quantidade atual de jogadores no elenco desta equipa
} Club;                                     // Nome da estrutura (pode ser usado como tipo Club)

// Declarações das funções públicas relacionadas com clubes

// Mostra o menu de gestão de equipas (diferente para ADM e usuário comum)
void menuEquipas(void);

// Cria e adiciona uma nova equipa ao sistema
void addClub(void);

// Lista todos os clubes cadastrados com detalhes básicos
void listClubs(void);

// Permite editar uma equipa existente (renomear, adicionar/remover jogadores, remover equipa)
void editClub(void);

// Mostra apenas visualização simples das equipas e jogadores (para usuário não-ADM)
void viewClubs(void);

// Retorna o número atual de clubes cadastrados
int getClubCount(void);

// Retorna ponteiro para o clube na posição 'index' (ou NULL se índice inválido)
Club* getClub(int index);

// Procura um clube pelo nome e retorna o índice no array (ou -1 se não existir)
int findClubIndex(const char *name);

// Declaração dos arrays e variáveis globais (definidos em club.c)
extern Club clubs[MAX_CLUBS];    // Array global que armazena todos os clubes cadastrados
extern int clubCount;            // Contador global: número atual de clubes no sistema

#endif                           // Fim da proteção contra inclusão múltipla