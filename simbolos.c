#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "simbolos.h"

// Tabela de símbolos
Simbolo tabela_simbolos[MAX_SIMBOLOS];
int num_simbolos = 0;

// Função para adicionar um identificador na tabela de símbolos (apenas token e lexema)
void adicionar_identificador(const char *lexema, const char *token)
{
    // Verifica se já existe o identificador na tabela de símbolos
    for (int i = 0; i < num_simbolos; i++)
    {
        if (strcmp(tabela_simbolos[i].lexema, lexema) == 0)
        {
            return;
        }
    }

    // Adiciona o novo identificador (apenas token e lexema)
    strcpy(tabela_simbolos[num_simbolos].lexema, lexema);
    strcpy(tabela_simbolos[num_simbolos].token, token);
    num_simbolos++;
}

// Função para exibir a tabela de símbolos
void exibir_tabela_simbolos()
{
    printf("\nTabela de Símbolos:\n");
    printf("%-15s %-10s\n", "Lexema", "Token");
    for (int i = 0; i < num_simbolos; i++)
    {
        printf("%-15s %-10s\n", tabela_simbolos[i].lexema, tabela_simbolos[i].token);
    }
}

// Função para inicializar todas as palavras reservadas na tabela de símbolos
void inicializar_palavras_reservadas()
{
    adicionar_identificador("funcao", "Palavra Reservada");
    adicionar_identificador("fimfuncao", "Palavra Reservada");
    adicionar_identificador("chama", "Palavra Reservada");
    adicionar_identificador("retorna", "Palavra Reservada");
    adicionar_identificador("tipo", "Palavra Reservada");
    adicionar_identificador("args", "Palavra Reservada");
    adicionar_identificador("fimargs", "Palavra Reservada");
    adicionar_identificador("escreva", "Palavra Reservada");
    adicionar_identificador("inteiro", "Palavra Reservada");
    adicionar_identificador("real", "Palavra Reservada");
    adicionar_identificador("caractere", "Palavra Reservada");
    adicionar_identificador("se", "Palavra Reservada");
    adicionar_identificador("entao", "Palavra Reservada");
    adicionar_identificador("senao", "Palavra Reservada");
    adicionar_identificador("fimse", "Palavra Reservada");
    adicionar_identificador("enquanto", "Palavra Reservada");
    adicionar_identificador("faca", "Palavra Reservada");
    adicionar_identificador("fimenquanto", "Palavra Reservada");
}