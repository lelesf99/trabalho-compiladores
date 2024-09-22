#ifndef SIMBOLOS_H
#define SIMBOLOS_H

#define MAX_SIMBOLOS 100
#define MAX_LEX 50
#define MAX_TOKEN 50


// Estrutura para armazenar os símbolos
typedef struct {
    char lexema[MAX_LEX];         // Nome do identificador
    char token[MAX_TOKEN];         // Nome do identificador
    // char escopo[10];             // Escopo do identificador (global, local, etc.)
    // int num_parametros;          // Número de parâmetros (para funções)
} Simbolo;

// Funções para manipulação da tabela de símbolos
void adicionar_identificador(const char *lexema, const char *token);
Simbolo *buscar_identificador(const char *lexema, const char *token);
void exibir_tabela_simbolos();

#endif
