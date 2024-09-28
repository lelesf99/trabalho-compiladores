#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "simbolos.h"

// Função de hash: Calcula o índice de um lexema na tabela hash
unsigned int funcao_hash(const char *lexema, int tamanho)
{
    unsigned int hash = 0;
    while (*lexema)
    {
        hash = (hash * 31) + *lexema++; // Usa um número primo para melhorar a distribuição
    }
    return hash % tamanho;
}

// Função para criar uma tabela de símbolos com um tamanho inicial
TabelaSimbolos *criar_tabela(int tamanho_inicial)
{
    TabelaSimbolos *tabela = (TabelaSimbolos *)malloc(sizeof(TabelaSimbolos));
    if (tabela == NULL)
    {
        fprintf(stderr, "Erro de alocação de memória\n");
        exit(1);
    }

    tabela->tamanho = tamanho_inicial;
    tabela->num_simbolos = 0;
    tabela->tabela = (Simbolo **)malloc(tamanho_inicial * sizeof(Simbolo *));
    if (tabela->tabela == NULL)
    {
        fprintf(stderr, "Erro de alocação de memória\n");
        exit(1);
    }

    for (int i = 0; i < tamanho_inicial; i++)
    {
        tabela->tabela[i] = NULL;
    }

    return tabela;
}

// Função para redimensionar a tabela hash quando necessário
void redimensionar_tabela(TabelaSimbolos *tabela)
{
    int novo_tamanho = tabela->tamanho * 2;
    Simbolo **nova_tabela = (Simbolo **)malloc(novo_tamanho * sizeof(Simbolo *));
    if (nova_tabela == NULL)
    {
        fprintf(stderr, "Erro de alocação de memória\n");
        exit(1);
    }

    for (int i = 0; i < novo_tamanho; i++)
    {
        nova_tabela[i] = NULL;
    }

    // Re-hash de todos os símbolos da tabela antiga para a nova
    for (int i = 0; i < tabela->tamanho; i++)
    {
        Simbolo *simbolo_atual = tabela->tabela[i];
        while (simbolo_atual != NULL)
        {
            Simbolo *proximo = simbolo_atual->proximo;
            unsigned int novo_indice = funcao_hash(simbolo_atual->lexema, novo_tamanho);
            simbolo_atual->proximo = nova_tabela[novo_indice];
            nova_tabela[novo_indice] = simbolo_atual;
            simbolo_atual = proximo;
        }
    }

    free(tabela->tabela); // Libera a tabela antiga
    tabela->tabela = nova_tabela;
    tabela->tamanho = novo_tamanho;
}

// Função para adicionar um identificador à tabela hash dinâmica
void adicionar_identificador(TabelaSimbolos *tabela, const char *lexema, const char *token)
{
    if ((float)tabela->num_simbolos / tabela->tamanho > HASH_LOAD_FACTOR)
    {
        redimensionar_tabela(tabela); // Redimensiona a tabela se o fator de carga for excedido
    }

    unsigned int indice = funcao_hash(lexema, tabela->tamanho);

    // Verifica se o identificador já existe na tabela hash
    Simbolo *atual = tabela->tabela[indice];
    while (atual != NULL)
    {
        if (strcmp(atual->lexema, lexema) == 0)
        {
            return; // Identificador já existe, não adiciona
        }
        atual = atual->proximo;
    }

    // Cria um novo símbolo e o insere na tabela hash
    Simbolo *novo = (Simbolo *)malloc(sizeof(Simbolo));
    if (novo == NULL)
    {
        fprintf(stderr, "Erro de alocação de memória\n");
        exit(1);
    }
    strcpy(novo->lexema, lexema);
    strcpy(novo->token, token);
    novo->proximo = tabela->tabela[indice]; // Insere no início da lista encadeada
    tabela->tabela[indice] = novo;
    tabela->num_simbolos++;
}

// Função para buscar um identificador na tabela hash
Simbolo *buscar_identificador(TabelaSimbolos *tabela, const char *lexema)
{
    unsigned int indice = funcao_hash(lexema, tabela->tamanho);
    Simbolo *atual = tabela->tabela[indice];

    // Percorre a lista encadeada no índice da tabela hash
    while (atual != NULL)
    {
        if (strcmp(atual->lexema, lexema) == 0)
        {
            return atual; // Identificador encontrado
        }
        atual = atual->proximo;
    }
    return NULL; // Identificador não encontrado
}

// Função para exibir a tabela de símbolos (hash table)
void exibir_tabela_simbolos(TabelaSimbolos *tabela)
{
    printf("\nTabela de Símbolos:\n");
    printf("%-15s %-10s\n", "Lexema", "Token");

    for (int i = 0; i < tabela->tamanho; i++)
    {
        Simbolo *atual = tabela->tabela[i];
        while (atual != NULL)
        {
            printf("%-15s %-10s\n", atual->lexema, atual->token);
            atual = atual->proximo;
        }
    }
}

// Função para inicializar as palavras reservadas
void inicializar_palavras_reservadas(TabelaSimbolos *tabela)
{
    adicionar_identificador(tabela, "funcao", "Palavra Reservada");
    adicionar_identificador(tabela, "fimfuncao", "Palavra Reservada");
    adicionar_identificador(tabela, "chama", "Palavra Reservada");
    adicionar_identificador(tabela, "retorna", "Palavra Reservada");
    adicionar_identificador(tabela, "tipo", "Palavra Reservada");
    adicionar_identificador(tabela, "args", "Palavra Reservada");
    adicionar_identificador(tabela, "fimargs", "Palavra Reservada");
    adicionar_identificador(tabela, "escreva", "Palavra Reservada");
    adicionar_identificador(tabela, "inteiro", "Palavra Reservada");
    adicionar_identificador(tabela, "real", "Palavra Reservada");
    adicionar_identificador(tabela, "caractere", "Palavra Reservada");
    adicionar_identificador(tabela, "se", "Palavra Reservada");
    adicionar_identificador(tabela, "entao", "Palavra Reservada");
    adicionar_identificador(tabela, "senao", "Palavra Reservada");
    adicionar_identificador(tabela, "fimse", "Palavra Reservada");
    adicionar_identificador(tabela, "enquanto", "Palavra Reservada");
    adicionar_identificador(tabela, "faca", "Palavra Reservada");
    adicionar_identificador(tabela, "fimenquanto", "Palavra Reservada");
}
