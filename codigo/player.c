#include <stdio.h>               // Biblioteca padrão para entrada/saída (usada em outros ficheiros, mas aqui não diretamente)
#include <string.h>              // Necessária para strcmp (comparação de strings) na função findPlayerIndex
#include "player.h"              // Header com definição da struct Player e constantes (MAX_PLAYERS, MAX_NAME, etc.)

// Array global que armazena todos os jogadores cadastrados no sistema
Player players[MAX_PLAYERS];     // Cada posição do array representa um jogador (struct Player)

// Contador global: mantém o número atual de jogadores cadastrados (0 no início)
int playerCount = 0;             // Incrementa sempre que um novo jogador é adicionado

// Função que procura um jogador pelo nome no array
// Retorna o índice (posição) no array se encontrar, ou -1 se não existir
int findPlayerIndex(const char *name) {
    for (int i = 0; i < playerCount; i++) {          // Percorre todos os jogadores já cadastrados
        if (strcmp(players[i].name, name) == 0) {    // Compara o nome do jogador atual com o nome procurado
            return i;                                // Encontrou → retorna o índice (posição) no array
        }
    }
    return -1;                                       // Não encontrou → retorna -1 (valor convencional para "não existe")
}

// Função que retorna um ponteiro para o jogador na posição 'index'
// Retorna NULL se o índice for inválido (menor que 0 ou maior/igual ao número de jogadores)
Player* getPlayer(int index) {
    // Verifica se o índice está dentro do intervalo válido
    return (index >= 0 && index < playerCount) ? &players[index] : NULL;
    // Se válido → retorna endereço do jogador na posição index
    // Se inválido → retorna NULL (ponteiro nulo)
}

// Função simples que retorna o número atual de jogadores cadastrados
int getPlayerCount(void) {
    return playerCount;          // Apenas devolve o valor da variável global playerCount
}