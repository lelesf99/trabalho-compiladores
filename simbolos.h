#ifndef SIMBOLOS_H
#define SIMBOLOS_H

#define MAX_LEX 100
#define MAX_TOKEN 20
#define HASH_LOAD_FACTOR 0.75  // Fator de carga antes de redimensionar

// Estrutura para armazenar lexemas e tokens
typedef struct Simbolo {
    char lexema[MAX_LEX];   // Nome do identificador
    char token[MAX_TOKEN];  // Tipo do token (Identificador, Palavra Reservada, etc.)
    struct Simbolo *proximo;  // Ponteiro para resolver colisões
} Simbolo;

// Tabela de símbolos (hash table dinâmica)
typedef struct {
    int tamanho;               // Tamanho da tabela hash
    int num_simbolos;          // Número de símbolos armazenados
    Simbolo **tabela;          // Ponteiro para o array de ponteiros (hash table)
} TabelaSimbolos;

// Funções para manipulação da tabela de símbolos
TabelaSimbolos *criar_tabela(int tamanho_inicial);
unsigned int funcao_hash(const char *lexema, int tamanho);
void adicionar_identificador(TabelaSimbolos *tabela, const char *lexema, const char *token);
Simbolo *buscar_identificador(TabelaSimbolos *tabela, const char *lexema);
void exibir_tabela_simbolos(TabelaSimbolos *tabela);
void inicializar_palavras_reservadas(TabelaSimbolos *tabela);
void redimensionar_tabela(TabelaSimbolos *tabela);

#endif
