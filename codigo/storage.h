#ifndef STORAGE_H               // Proteção contra inclusão múltipla: evita erros se o header for incluído mais de uma vez no mesmo ficheiro
#define STORAGE_H                // Define o símbolo STORAGE_H para marcar que este header já foi incluído

// Declaração da função que carrega todos os dados salvos do ficheiro (jogadores, clubes, partidas)
void loadAllData(void);

// Declaração da função que salva todos os dados atuais no ficheiro (sobrescreve o anterior)
void saveAllData(void);

#endif                           // Fim da proteção contra inclusão múltipla