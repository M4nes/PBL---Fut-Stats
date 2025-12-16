#ifndef PLAYER_H
#define PLAYER_H

#define MAX_JOGADORES 200

typedef struct {
    int id;
    char nome[50];
    int idade;
    int clubeId;
    int ativo;
} Jogador;

void inicializarJogadores();
void adicionarJogador();
void listarJogadoresPorClube();
void editarJogador();
void removerJogador();

extern Jogador jogadores[MAX_JOGADORES];

#endif
