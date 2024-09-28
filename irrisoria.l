%{
#include <stdio.h>
#include <stdlib.h>
#include "simbolos.h"

void yyerror(const char *s);
void inicializar_palavras_reservadas();  // Função para inicializar as palavras reservadas

int linha_atual = 1;

%}

%option noyywrap

D [0-9]
L [a-zA-Z]
S [~`!@#$%\^&\*\(\)_\-\+\\\/\[\]\{\}\|'\?\>\<\.,=]

%%

"funcao" { printf("funcao\n"); }
"fimfuncao" { printf("fimfuncao\n"); }
"chama" { printf("chama\n"); }
"retorna" { printf("retorna\n"); }
"tipo" { printf("tipo\n"); }
"args" { printf("args\n"); }
"fimargs" { printf("fimargs\n"); }
"escreva" { printf("escreva\n"); }
"inteiro" { printf("inteiro\n"); }
"real" { printf("real\n"); }
"caractere" { printf("caractere\n"); }
"se" { printf("se\n"); }
"entao" { printf("entao\n"); }
"senao" { printf("senao\n"); }
"fimse" { printf("fimse\n"); }
"enquanto" { printf("enquanto\n"); }
"faca" { printf("faca\n"); }
"fimenquanto" { printf("fimenquanto\n"); }

{D}+(\.{D}+)?([Ee][\+\-]?{D}+)? { printf("CONST_NUM: %s\n", yytext); adicionar_identificador(yytext, "CONST_NUM"); }

\"({L}|{D}|{S}|\ |\t)*\" { printf("CONST_LIT: %s\n", yytext); adicionar_identificador(yytext, "CONST_LIT"); }

@ { printf("CHAMADA_FUNCAO: %s\n", yytext); adicionar_identificador(yytext, "CHAMADA_FUNCAO"); }

{L}({L}|{D}|_)* { printf("ID_OU_FUNCAO: %s\n", yytext); adicionar_identificador(yytext, "ID_OU_FUNCAO"); }

("<"|">"|">="|"<="|"=="|"<>") { printf("OP_RELACIONAL: %s\n", yytext); }

("+"|"-"|"*"|"/") { printf("OP_ARITMETICO: %s\n", yytext); }

\= { printf("ATRIBUICAO: %s\n", yytext); }

\( { printf("ABRE_PAR\n"); }
\) { printf("FECHA_PAR\n"); }
, { printf("VIRGULA\n"); }
; { printf("PONTO_E_VIRGULA\n"); }

[ \t\r\n]+

\{({L}|{D}|{S}|\ |\t)*\} { printf("COMENTARIO\n"); }

<<EOF>> { printf("FIM_DE_ARQ\n"); return 0; }

. { yyerror("erro"); }

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro léxico: %s\n", s);
}

int main(int argc, char **argv) {
    inicializar_palavras_reservadas();  // Inicializa as palavras reservadas
    yylex();
    exibir_tabela_simbolos();
    return 0;
}