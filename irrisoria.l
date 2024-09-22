%{
#include <stdio.h>
#include <stdlib.h>
#include "simbolos.h"  // Incluir o cabeçalho da tabela de símbolos

void yyerror(const char *s);

#include <stdio.h>
#include <stdlib.h>

int linha_atual = 1;

%}

%option noyywrap

/* Primeiras definicoes */
D [0-9]
L [a-zA-Z]
/* {~, `, !, @, #, $, %, ^, &, *, (, ), _, -, +, \, /, [, ], {, }, |,', ?, >, <, ., ,} */
/* operators : " \ { } [ ] ^ $ < > ? . * + | () / */
S [~`!@#$%\^&\*\(\)_\-\+\\\/\[\]\{\}\|'\?\>\<\.,]

/* regexes de tokens */
/* CONST_NUM D+(\.D+)?((E|e)(\+|-)?D+)?     Constante numérica  */
/* CONST_LIT \"([LDS \t])*\"                Constante literal  */
/* CHAMADA_FUNCAO @                         Chamada de função  */
/* ID_OU_FUNCAO {L}({L}|{D}|_)*             Nome de variável ou função  */
/* OP_RELACIONAL <|>|>=|<=|==|<>            Operador relacional  */
/* OP_ARITMETICO \+|\-|\*|\/                Operador aritmético  */
/* ATRIBUICAO =                             Atribuição  */
/* ABRE_PAR \(                              Abre parênteses  */
/* ABRE_PAR \)                              Fecha parênteses  */
/* VIRGULA ,                                Vírgula  */
/* PONTO_E_VIRGULA ;                        Ponto e vírgula  */
/* VAZIO ([ \t\r\n])+                       Espaço, tabulação, e salto de linha  */
/* COMENTARIO \{([LDS \t])*\}               Comentários  */
/* EOF                                      Fim do arquivo  */

 
/* A tabela a seguir descreve os lexemas que devem ser identificados para geração de tokens pelo */
/* analisador léxico para a linguagem Irrisória. */

/* funcao – Delimita o início de uma função. */
/* fimfuncao – Delimita o fim de uma função. */
/* chama – Chama uma função. */
/* retorna – Encerra uma função, opcionalmente retornando um valor. */
/* tipo – Indica que a função tem um tipo. */
/* args – Delimita o início dos argumentos passados como entrada para uma função. */
/* fimargs – Delimita o fim dos argumentos passados como entrada para uma função. */
/* escreva – Escreve na saída padrão. */
/* inteiro – Tipo de dado inteiro. */
/* real – Tipo de dado real. */
/* caractere – Tipo de dado caractere. */
/* se – Elemento de estrutura condicional. */
/* entao – Elemento de estrutura condicional. */
/* senao – Elemento de estrutura condicional. */
/* fimse – Elemento de estrutura condicional. */
/* enquanto – Elemento de estrutura de repetição. */
/* faca – Elemento de estrutura de repetição. */
/* fimenquanto – Elemento de estrutura de repetição. */

%%

"funcao" {printf("funcao"); adicionar_identificador(yytext, "funcao"); }
"fimfuncao" {printf("fimfuncao"); adicionar_identificador(yytext, "fimfuncao"); }
"chama" {printf("chama"); adicionar_identificador(yytext, "chama"); }
"retorna" {printf("retorna"); adicionar_identificador(yytext, "retorna"); }
"tipo" {printf("tipo"); adicionar_identificador(yytext, "tipo"); }
"args" {printf("args"); adicionar_identificador(yytext, "args"); }
"fimargs" {printf("fimargs"); adicionar_identificador(yytext, "fimargs"); }
"escreva" {printf("escreva"); adicionar_identificador(yytext, "escreva"); }
"inteiro" {printf("inteiro"); adicionar_identificador(yytext, "inteiro"); }
"caractere" {printf("caractere"); adicionar_identificador(yytext, "caractere"); }
"se" {printf("se"); adicionar_identificador(yytext, "se"); }
"entao" {printf("entao"); adicionar_identificador(yytext, "entao"); }
"senao" {printf("senao"); adicionar_identificador(yytext, "senao"); }
"fimse" {printf("fimse"); adicionar_identificador(yytext, "fimse"); }
"enquanto" {printf("enquanto"); adicionar_identificador(yytext, "enquanto"); }
"faca" {printf("faca"); adicionar_identificador(yytext, "faca"); }
"fimenquanto" {printf("fimenquanto"); adicionar_identificador(yytext, "fimenquanto"); }


{D}+(\.{D}+)?([Ee][\+\-]?{D}+)? { printf("CONST_NUM"); adicionar_identificador( yytext, "CONST_NUM"); }
\"({L}|{D}|{S}|\ |\t)*\" { printf("CONST_LIT"); adicionar_identificador( yytext, "CONST_LIT"); }
@ { printf("CHAMADA_FUNCAO"); adicionar_identificador( yytext, "CHAMADA_FUNCAO"); }
{L}({L}|{D}|_)* { printf("ID_OU_FUNCAO"); adicionar_identificador( yytext, "ID_OU_FUNCAO"); }
("<"|">"|">="|"<="|"=="|"<>") { printf("OP_RELACIONAL"); adicionar_identificador( yytext, "OP_RELACIONAL"); }
("+"|"-"|"*"|"/") { printf("OP_ARITMETICO"); adicionar_identificador( yytext, "OP_ARITMETICO"); }
\= { printf("ATRIBUICAO"); adicionar_identificador( yytext, "ATRIBUICAO"); }
\( { printf("ABRE_PARENTESE"); adicionar_identificador( yytext, "ABRE_PARENTESE"); }
\) { printf("FECHA_PARENTESE"); adicionar_identificador( yytext, "FECHA_PARENTESE"); }
, { printf("VIRGULA"); adicionar_identificador( yytext, "VIRGULA"); }
; { printf("PONTO_E_VIRGULA"); adicionar_identificador( yytext, "PONTO_E_VIRGULA"); }
[ \t\r\n]+ { printf(yytext); adicionar_identificador( yytext, "VAZIO"); }

\{({L}|{D}|{S}|\ |\t)*\} { printf("COMENTARIO"); adicionar_identificador( yytext, "COMENTARIO"); }

. { yyerror("Caractere inválido"); }
%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro léxico: %s\n", s);
}

int main(int argc, char **argv) {
    yylex();  // Inicia o analisador léxico
    exibir_tabela_simbolos();  // Exibe a tabela de símbolos ao final
    return 0;
}

