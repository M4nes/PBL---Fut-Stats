#ifndef CLUB_H
#define CLUB_H

#define MAX_CLUBES 50

typedef struct {
    int id;
    char nome[50];
    int ativo;
} Clube;

void inicializarClubes();
void criarClube();
void listarClubes();
void editarClube();
void removerClube();
int escolherClube();

extern Clube clubes[MAX_CLUBES];

#endif
