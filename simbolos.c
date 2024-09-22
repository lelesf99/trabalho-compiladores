#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "simbolos.h"

// Tabela de símbolos
Simbolo tabela_simbolos[MAX_SIMBOLOS];
int num_simbolos = 0;

// Função para adicionar um identificador na tabela de símbolos
void adicionar_identificador(const char *lexema, const char *token)
{
    // Adiciona o novo identificador
    strcpy(tabela_simbolos[num_simbolos].lexema, lexema);
    strcpy(tabela_simbolos[num_simbolos].token, token);
    num_simbolos++;
}

// // Função para buscar um identificador
// Simbolo *buscar_identificador(const char *nome, const char *escopo) {
//     for (int i = 0; i < num_simbolos; i++) {
//         if (strcmp(tabela_simbolos[i].nome, nome) == 0 && strcmp(tabela_simbolos[i].escopo, escopo) == 0) {
//             return &tabela_simbolos[i];
//         }
//     }
//     return NULL;  // Retorna NULL se não encontrar o identificador
// }

// Comparison function for qsort
int compareTokens(const void *a, const void *b)
{
    return strcmp(((Simbolo *)a)->token, ((Simbolo *)b)->token);
}

// Função para exibir a tabela de símbolos
void exibir_tabela_simbolos()
{
    qsort(tabela_simbolos, num_simbolos, sizeof(Simbolo), compareTokens);
    printf("\nTabela de Símbolos:\n");
    printf("%-30s %-10s\n", "Lexema", "Token");
    for (int i = 0; i < num_simbolos; i++)
    {
        char *lexema = tabela_simbolos[i].lexema;
        char *token = tabela_simbolos[i].token;

        if (strcmp(token, "VAZIO") == 0)
        {
            printf("%-30s %-10s\n",
                   " ",
                   tabela_simbolos[i].token);
        }
        else
        {
            printf("%-30s %-10s\n",
                   tabela_simbolos[i].lexema,
                   tabela_simbolos[i].token);
        }
    }
}
