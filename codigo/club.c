#include <stdio.h>               // Biblioteca padrão para entrada/saída (printf, scanf, getchar)
#include <string.h>              // Para strcmp, strcpy, strlen, etc. (muito usado em nomes e comparações)
#include <stdlib.h>              // Para rand() e srand() no modo automático de geração de jogadores
#include "club.h"                // Header com definição da struct Club, constantes e declarações de funções
#include "player.h"              // Header com struct Player e funções relacionadas (getPlayer, findPlayerIndex, etc.)
#include "storage.h"             // Header com funções de salvar/carregar dados (saveAllData)
#include "menu.h"                // Header com funções de menu e utilitários (clearScreen, cores ORANGE/BOLD/RESET)

// Declaração externa da variável global definida em main.c (indica se é administrador)
extern int isAdm;

// Definições de cores ANSI (copiadas para independência do ficheiro menu.c)
#define ORANGE "\033[38;5;208m"  // Código ANSI para cor laranja no terminal
#define BOLD   "\033[1m"         // Código ANSI para texto em negrito
#define RESET  "\033[0m"         // Código ANSI para resetar cor e estilo

// Array global que armazena todos os clubes cadastrados no sistema
Club clubs[MAX_CLUBS];           // Cada posição é um clube (struct Club)

// Contador global: mantém o número atual de clubes cadastrados (0 no início)
int clubCount = 0;

// Função que permite ao usuário comum (não-ADM) apenas visualizar as equipas e seus jogadores
void viewClubs(void) {
    if (clubCount == 0) {        // Verifica se não há nenhum clube cadastrado
        printf("%sNenhuma equipa cadastrada.%s\n", ORANGE, RESET);
        printf("%sPressione ENTER para continuar...%s", ORANGE, RESET);
        getchar(); getchar();    // Espera o usuário pressionar ENTER duas vezes (consome buffer)
        return;                  // Sai da função imediatamente
    }

    clearScreen();               // Limpa a tela do terminal antes de mostrar a lista
    printf("\n%s=== VISUALIZAÇÃO DE EQUIPAS (%d) ===%s\n", ORANGE BOLD, clubCount, RESET);

    // Percorre todos os clubes cadastrados
    for (int i = 0; i < clubCount; i++) {
        // Mostra o número e nome do clube em destaque laranja
        printf("\n[%d] %s%s (%d jogadores)%s\n", i+1, ORANGE, clubs[i].name, clubs[i].playerCount, RESET);

        // Mostra cada jogador do elenco do clube atual
        for (int j = 0; j < clubs[i].playerCount; j++) {
            // Obtém o ponteiro para o jogador na posição armazenada
            Player *p = getPlayer(clubs[i].playerIndexes[j]);
            // Mostra nome, número da camisola, posição, nacionalidade e idade
            printf("  • %s%s #%d (%s) - %s, %d anos%s\n", ORANGE, p->name, p->shirtNumber, p->position, p->nationality, p->age, RESET);
        }
    }

    // Mensagem final para o usuário saber que pode voltar
    printf("\n%sPressione ENTER para voltar...%s", ORANGE, RESET);
    getchar(); getchar();        // Espera ENTER (duas vezes para consumir buffer)
}

// Função que adiciona uma nova equipa ao sistema (apenas ADM)
void addClub(void) {
    if (clubCount >= MAX_CLUBS) {   // Verifica se já atingiu o limite máximo de clubes
        printf("%sLimite de equipas atingido!%s\n", ORANGE, RESET);
        return;                      // Sai da função sem fazer nada
    }

    Club newClub;                    // Variável local para armazenar a nova equipa
    clearScreen();                   // Limpa a tela para uma interface mais limpa
    printf("\n%s=== NOVA EQUIPA ===%s\n", ORANGE BOLD, RESET);
    printf("Nome da equipa: ");
    scanf(" %49[^\n]", newClub.name);  // Lê o nome (permite espaços, até 49 caracteres)

    // Verifica se já existe um clube com esse nome
    if (findClubIndex(newClub.name) != -1) {
        printf("%sEquipa já existe!%s\n", ORANGE, RESET);
        getchar(); getchar();        // Espera ENTER para o usuário ler a mensagem
        return;                      // Sai sem criar o clube
    }

    newClub.playerCount = 0;         // Inicia o elenco vazio

    int modo;                        // Variável para escolher modo de adição de jogadores
    do {
        printf("\n%sModo de adição de jogadores:%s\n", ORANGE, RESET);
        printf("1. Manual (digitar um por um)\n");
        printf("2. Automático (11 jogadores aleatórios)\n");
        printf("Escolha: ");
        scanf("%d", &modo);          // Lê a escolha do utilizador
    } while (modo != 1 && modo != 2);  // Repete até ser 1 ou 2

    if (modo == 1) {
        // Modo manual: o utilizador digita cada jogador
        while (newClub.playerCount < MAX_PLAYERS_PER_CLUB) {
            char inputName[50];
            printf("Nome do jogador %d (ou '0' para parar): ", newClub.playerCount + 1);
            scanf(" %49[^\n]", inputName);

            if (strcmp(inputName, "0") == 0) break;  // Usuário escolheu parar

            // Verifica se o nome já existe no sistema
            if (findPlayerIndex(inputName) != -1) {
                printf("%sNome já existe!%s\n", ORANGE, RESET);
                continue;                    // Volta ao início do ciclo
            }

            Player newPlayer;                // Estrutura temporária para o novo jogador
            strcpy(newPlayer.name, inputName);

            int shirt;                       // Número da camisola
            int valid = 0;                   // Flag para validar o número
            do {
                printf("Número da camisa (1-99): ");
                scanf("%d", &shirt);
                if (shirt < 1 || shirt > 99) {
                    printf("%sNúmero inválido!%s\n", ORANGE, RESET);
                    continue;
                }
                valid = 1;                   // Assume válido até prova em contrário
                for (int j = 0; j < newClub.playerCount; j++) {
                    Player *p = getPlayer(newClub.playerIndexes[j]);
                    if (p->shirtNumber == shirt) {  // Verifica se o número já está em uso no clube
                        printf("%sNúmero %d já usado por %s!%s\n", ORANGE, shirt, p->name, RESET);
                        valid = 0;
                        break;
                    }
                }
            } while (!valid);                // Repete até o número ser válido e único

            newPlayer.shirtNumber = shirt;

            printf("Idade: ");
            scanf("%d", &newPlayer.age);

            printf("Nacionalidade: ");
            scanf(" %49[^\n]", newPlayer.nationality);

            printf("Posição: ");
            scanf(" %29[^\n]", newPlayer.position);

            printf("Último clube (ou 'Nenhum'): ");
            scanf(" %49[^\n]", newPlayer.lastClub);

            strcpy(newPlayer.currentClub, newClub.name);  // Define o clube atual
            newPlayer.careerGoals = 0;                    // Inicia com zero golos na carreira

            // Adiciona o jogador ao array global de jogadores
            players[playerCount] = newPlayer;
            // Adiciona o índice do jogador ao elenco do novo clube
            newClub.playerIndexes[newClub.playerCount++] = playerCount++;
            printf("%sJogador '%s' #%d adicionado!%s\n\n", ORANGE, inputName, shirt, RESET);
        }
    } else {
        // Modo automático: gera 11 jogadores aleatórios
        printf("%sGerando 11 jogadores automáticos...%s\n", ORANGE, RESET);
        // Lista de nomes base para gerar nomes aleatórios
        const char *nomes[] = {"João Silva", "Pedro Santos", "Lucas Oliveira", "Mateus Costa", "Gabriel Souza", "Rafael Pereira", "Felipe Almeida", "Bruno Rodrigues", "Vinicius Lima", "Thiago Ferreira", "Leonardo Martins"};
        // Lista de posições possíveis
        const char *posicoes[] = {"Goleiro", "Zagueiro", "Lateral", "Volante", "Meia", "Atacante"};

        for (int i = 0; i < 11; i++) {   // Gera exatamente 11 jogadores
            Player newPlayer;
            // Cria nome combinando nome base + número (ex: João Silva 1)
            sprintf(newPlayer.name, "%s %d", nomes[i % 11], i+1);
            newPlayer.shirtNumber = i+1;               // Camisas de 1 a 11
            newPlayer.age = 18 + rand() % 18;          // Idade aleatória entre 18 e 35
            strcpy(newPlayer.nationality, "Brasil");   // Nacionalidade fixa (pode mudar se quiseres)
            strcpy(newPlayer.position, posicoes[rand() % 6]);  // Posição aleatória da lista
            strcpy(newPlayer.lastClub, "Formação");    // Último clube fictício
            strcpy(newPlayer.currentClub, newClub.name);  // Define o clube atual
            newPlayer.careerGoals = 0;                 // Zero golos na carreira

            // Adiciona ao array global de jogadores
            players[playerCount] = newPlayer;
            newClub.playerIndexes[newClub.playerCount++] = playerCount++;
        }
        printf("%s11 jogadores gerados!%s\n", ORANGE, RESET);
    }

    // Adiciona o novo clube ao array global
    clubs[clubCount++] = newClub;
    saveAllData();                       // Salva imediatamente no ficheiro
    printf("%sEquipa '%s' criada com sucesso!%s\n", ORANGE BOLD, newClub.name, RESET);
    getchar(); getchar();                // Espera ENTER para o utilizador ler a mensagem
}

// Lista todos os clubes e seus jogadores (usada por ADM e visualização)
void listClubs(void) {
    if (clubCount == 0) {                // Verifica se não há clubes
        printf("%sNenhuma equipa cadastrada.%s\n", ORANGE, RESET);
        getchar(); getchar();
        return;
    }

    clearScreen();                       // Limpa a tela antes de mostrar
    printf("\n%s=== LISTA DE EQUIPAS (%d) ===%s\n", ORANGE BOLD, clubCount, RESET);

    for (int i = 0; i < clubCount; i++) {
        // Mostra número, nome e quantidade de jogadores
        printf("\n[%d] %s%s (%d jogadores)%s\n", i+1, ORANGE, clubs[i].name, clubs[i].playerCount, RESET);

        // Mostra cada jogador do clube
        for (int j = 0; j < clubs[i].playerCount; j++) {
            Player *p = getPlayer(clubs[i].playerIndexes[j]);
            printf("  • %s%s #%d (%s)%s\n", ORANGE, p->name, p->shirtNumber, p->position, RESET);
        }
    }

    printf("\n%sPressione ENTER para continuar...%s", ORANGE, RESET);
    getchar(); getchar();
}

// Função completa de edição de uma equipa (apenas ADM)
void editClub(void) {
    if (clubCount == 0) {                // Verifica se há clubes para editar
        printf("%sNenhuma equipa para editar.%s\n", ORANGE, RESET);
        getchar(); getchar();
        return;
    }

    listClubs();                         // Mostra a lista para o utilizador escolher

    printf("\n%sDigite o número da equipa para editar (0 para cancelar): %s", ORANGE, RESET);
    int choice;
    scanf("%d", &choice);
    if (choice == 0) return;             // Cancelou
    choice--;                            // Ajusta para índice baseado em 0

    if (choice < 0 || choice >= clubCount) {
        printf("%sEquipa inválida!%s\n", ORANGE, RESET);
        getchar(); getchar();
        return;
    }

    Club *c = &clubs[choice];            // Ponteiro para o clube selecionado

    int op;                              // Variável para opções do sub-menu
    do {
        clearScreen();                   // Limpa tela a cada ciclo do sub-menu
        printf("\n%sEditar Equipa: %s%s\n", ORANGE BOLD, c->name, RESET);
        printf("1. Renomear equipa\n");
        printf("2. Adicionar jogador\n");
        printf("3. Remover jogador\n");
        printf("4. Remover equipa inteira\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch (op) {
            case 1:                      // Renomear o clube
                printf("Novo nome: ");
                scanf(" %49[^\n]", c->name);
                // Atualiza o nome do clube atual em todos os jogadores do elenco
                for (int j = 0; j < c->playerCount; j++) {
                    Player *p = getPlayer(c->playerIndexes[j]);
                    strcpy(p->currentClub, c->name);
                }
                saveAllData();           // Salva as alterações
                printf("%sNome alterado!%s\n", ORANGE, RESET);
                break;

            case 2:                      // Adicionar jogador ao elenco
                if (c->playerCount >= MAX_PLAYERS_PER_CLUB) {
                    printf("%sElenco cheio!%s\n", ORANGE, RESET);
                    break;
                }
                printf("Nome do jogador (deve existir): ");
                char name[50];
                scanf(" %49[^\n]", name);
                int idx = findPlayerIndex(name);
                if (idx == -1) {
                    printf("%sJogador não encontrado!%s\n", ORANGE, RESET);
                } else {
                    int already = 0;
                    // Verifica se o jogador já está no elenco
                    for (int j = 0; j < c->playerCount; j++) {
                        if (c->playerIndexes[j] == idx) already = 1;
                    }
                    if (already) {
                        printf("%sJogador já está no elenco!%s\n", ORANGE, RESET);
                    } else {
                        // Adiciona o índice do jogador ao clube
                        c->playerIndexes[c->playerCount++] = idx;
                        Player *p = getPlayer(idx);
                        strcpy(p->currentClub, c->name);  // Atualiza clube atual do jogador
                        saveAllData();
                        printf("%sJogador adicionado!%s\n", ORANGE, RESET);
                    }
                }
                break;

            case 3:                      // Remover jogador do elenco
                if (c->playerCount == 0) {
                    printf("%sElenco vazio!%s\n", ORANGE, RESET);
                    break;
                }
                printf("Número do jogador para remover (1 a %d): ", c->playerCount);
                int rem;
                scanf("%d", &rem);
                rem--;                       // Ajusta para índice baseado em 0
                if (rem < 0 || rem >= c->playerCount) {
                    printf("%sNúmero inválido!%s\n", ORANGE, RESET);
                } else {
                    int playerIdx = c->playerIndexes[rem];
                    Player *p = getPlayer(playerIdx);
                    strcpy(p->currentClub, "Sem clube");  // Libera o jogador
                    // Remove o jogador do array do clube (desloca os restantes)
                    for (int k = rem; k < c->playerCount - 1; k++) {
                        c->playerIndexes[k] = c->playerIndexes[k + 1];
                    }
                    c->playerCount--;
                    saveAllData();
                    printf("%sJogador removido do elenco!%s\n", ORANGE, RESET);
                }
                break;

            case 4:                      // Remover a equipa inteira
                printf("%sTem certeza que quer REMOVER a equipa '%s'? (s/n): %s", ORANGE, c->name, RESET);
                char confirm;
                scanf(" %c", &confirm);
                if (confirm == 's' || confirm == 'S') {
                    // Libera todos os jogadores do clube
                    for (int j = 0; j < c->playerCount; j++) {
                        Player *p = getPlayer(c->playerIndexes[j]);
                        strcpy(p->currentClub, "Sem clube");
                    }
                    // Remove o clube da lista global (desloca os restantes)
                    for (int i = choice; i < clubCount - 1; i++) {
                        clubs[i] = clubs[i + 1];
                    }
                    clubCount--;
                    saveAllData();
                    printf("%sEquipa removida com sucesso!%s\n", ORANGE, RESET);
                    return;                  // Sai da função após remoção
                }
                break;

            case 0:
                break;                   // Volta ao menu anterior

            default:
                printf("%sOpção inválida!%s\n", ORANGE, RESET);
        }

        if (op != 0) {                   // Se não saiu (op != 0), espera ENTER
            printf("%sPressione ENTER para continuar...%s", ORANGE, RESET);
            getchar(); getchar();
        }
    } while (op != 0);                   // Repete até escolher 0
}

// Retorna o número atual de clubes cadastrados
int getClubCount(void) {
    return clubCount;
}

// Retorna ponteiro para o clube na posição index (ou NULL se inválido)
Club* getClub(int index) {
    return (index >= 0 && index < clubCount) ? &clubs[index] : NULL;
}

// Procura um clube pelo nome e retorna o índice (ou -1 se não existir)
int findClubIndex(const char *name) {
    for (int i = 0; i < clubCount; i++) {
        if (strcmp(clubs[i].name, name) == 0) return i;
    }
    return -1;
}

// Menu de gestão de equipas (diferente para ADM e usuário comum)
void menuEquipas(void) {
    if (!isAdm) {                        // Se não for administrador
        viewClubs();                     // Apenas mostra visualização simples
        return;
    }

    int op;
    do {
        clearScreen();                   // Limpa a tela
        printf("\n%s--- GESTÃO DE EQUIPAS (ADM) ---%s\n", ORANGE BOLD, RESET);
        printf("1. Adicionar equipa\n");
        printf("2. Listar equipas\n");
        printf("3. Editar equipa\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch (op) {
            case 1: addClub(); break;
            case 2: listClubs(); break;
            case 3: editClub(); break;
            case 0: break;
            default: printf("%sOpção inválida!%s\n", ORANGE, RESET); getchar(); getchar();
        }
    } while (op != 0);                   // Sai apenas quando escolher 0
}