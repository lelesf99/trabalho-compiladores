#ifndef SIMBOLOS_H
#define SIMBOLOS_H

#define MAX_SIMBOLOS 100
#define MAX_LEX 50
#define MAX_TOKEN 50

// Estrutura para armazenar os símbolos
typedef struct
{
    char lexema[MAX_LEX];  // Lexema (o nome do identificador)
    char token[MAX_TOKEN]; // Tipo de token (Identificador, Palavra Reservada, etc.)
} Simbolo;

// Funções para manipulação da tabela de símbolos
void adicionar_identificador(const char *lexema, const char *token);
Simbolo *buscar_identificador(const char *lexema);
void exibir_tabela_simbolos();

#endif