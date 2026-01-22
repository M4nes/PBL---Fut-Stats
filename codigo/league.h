#ifndef LEAGUE_H                 // Proteção contra inclusão múltipla: evita erros se o header for incluído mais de uma vez no mesmo ficheiro
#define LEAGUE_H                  // Define o símbolo LEAGUE_H para marcar que este header já foi incluído

#include "club.h"                 // Necessário para usar struct Club e funções relacionadas (getClub, findClubIndex, clubCount)
#include "match.h"                // Necessário para usar struct Match e array matches[] (para calcular estatísticas dos jogos)

// Declaração da função principal deste módulo: calcula e mostra a tabela de classificação completa
void showLeagueTable(void);

#endif                            // Fim da proteção contra inclusão múltipla