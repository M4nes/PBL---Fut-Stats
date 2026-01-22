#ifndef MATCH_H                  // Proteção contra inclusão múltipla: evita erros se o header for incluído mais de uma vez no mesmo ficheiro
#define MATCH_H                   // Define o símbolo MATCH_H para marcar que este header já foi incluído

#include "club.h"                 // Necessário para usar struct Club (para clubA e clubB na struct Match)

#define MAX_MATCHES 200           // Constante que define o tamanho máximo do array de partidas/jogos que o sistema pode armazenar

// Definição da estrutura que representa uma partida/jogo entre duas equipas
typedef struct {
    Club *clubA;                  // Ponteiro para a primeira equipa (clube A)
    Club *clubB;                  // Ponteiro para a segunda equipa (clube B)
    int scoreA;                   // Gólos marcados pela equipa A
    int scoreB;                   // Gólos marcados pela equipa B
    int shotsA;                   // Total de chutes da equipa A
    int shotsOnTargetA;           // Chutes no alvo da equipa A
    int possessionA;              // Percentagem de posse de bola da equipa A (0-100)
    int shotsB;                   // Total de chutes da equipa B
    int shotsOnTargetB;           // Chutes no alvo da equipa B
    int possessionB;              // Percentagem de posse de bola da equipa B (0-100)
} Match;                          // Nome da estrutura (pode ser usado como tipo Match)

// Declarações das funções públicas relacionadas com partidas/jogos

// Mostra o menu de registo de jogos (opções manual, aleatório, torneio)
void menuJogos(void);

// Permite ao utilizador escolher duas equipas e simular um jogo manualmente
void playManualMatch(void);

// Sorteia aleatoriamente duas equipas e simula um jogo
void playRandomMatch(void);

// Gera placar e estatísticas aleatórias para uma partida (usada em todos os tipos de simulação)
void generateRandomMatch(Match *m);

// Mostra o resultado de uma partida com formatação bonita e cores
void printMatchResult(const Match *m);

// Lista o histórico completo de todas as partidas registradas
void listMatchHistory(void);

// Declaração dos arrays e variáveis globais (definidos em match.c)
extern Match matches[MAX_MATCHES];   // Array global que armazena todas as partidas disputadas
extern int matchCount;               // Contador global: número atual de partidas registradas

#endif                               // Fim da proteção contra inclusão múltipla