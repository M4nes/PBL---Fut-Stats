#ifndef PLAYER_H               // Proteção contra inclusão múltipla: evita erros se o header for incluído mais de uma vez
#define PLAYER_H                // Define o símbolo PLAYER_H para marcar que este header já foi incluído

// Constantes que definem os limites máximos das estruturas e strings
#define MAX_PLAYERS 500         // Número máximo de jogadores que o sistema pode armazenar
#define MAX_NAME 50             // Tamanho máximo do nome do jogador (inclui o '\0' final)
#define MAX_NATIONALITY 50      // Tamanho máximo da string de nacionalidade
#define MAX_POSITION 30         // Tamanho máximo da string de posição (ex: "Atacante", "Zagueiro")
#define MAX_CLUB 50             // Tamanho máximo do nome do clube

// Definição da estrutura (struct) que representa um jogador
typedef struct {
    char name[MAX_NAME];             // Nome completo do jogador
    int shirtNumber;                 // Número da camisola (1 a 99, único por clube)
    int age;                         // Idade do jogador (em anos)
    char nationality[MAX_NATIONALITY]; // Nacionalidade do jogador (ex: "Portugal", "Brasil")
    char position[MAX_POSITION];     // Posição principal no campo (ex: "Goleiro", "Meia")
    char lastClub[MAX_CLUB];         // Nome do último clube onde jogou (ou "Nenhum")
    char currentClub[MAX_CLUB];      // Nome do clube atual (ou "Sem clube")
    int careerGoals;                 // Total de golos marcados na carreira
} Player;                            // Nome da estrutura (agora pode ser usado como tipo Player)

// Declarações das funções públicas relacionadas com jogadores
// Procura um jogador pelo nome e retorna o índice no array (ou -1 se não existir)
int findPlayerIndex(const char *name);

// Retorna um ponteiro para o jogador na posição 'index' (ou NULL se índice inválido)
Player* getPlayer(int index);

// Retorna o número atual de jogadores cadastrados no sistema
int getPlayerCount(void);

// Declaração dos arrays e variáveis globais (definidos em player.c)
extern Player players[MAX_PLAYERS];   // Array global que armazena todos os jogadores
extern int playerCount;               // Contador global: número atual de jogadores cadastrados

#endif                                // Fim da proteção contra inclusão múltipla