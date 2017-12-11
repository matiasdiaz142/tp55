%code top{
#include <stdio.h>
#include "scanner.h"

#include "semantic.h"
}
%code provides{
void yyerror(const char *);
extern int yylexerrs;
}
%defines "parser.h"
%output "parser.c"
%token IDENTIFICADOR PROGRAMA FIN LEER ESCRIBIR VARIABLES CODIGO  DEFINIR CONSTANTE
%token ASIGNACION ":="
%left '-' '+'
%left '*' '/'
%precedence NEG
%define api.value.type {char *}
%define parse.error verbose
%%

todo : {load();} PROGRAMA definicionVariables definicionCodigo FIN { if (yynerrs || yylexerrs) YYABORT; stop();} ;
definicionVariables : VARIABLES listaVariables ;
listaVariables : unaVariable
	| listaVariables unaVariable
	;
unaVariable : DEFINIR IDENTIFICADOR ';' {definirIdentificador($IDENTIFICADOR);}
	| error ';'
	;
definicionCodigo : CODIGO listaSentencias ;
listaSentencias : sentencia
	| listaSentencias sentencia
	;
sentencia : LEER '(' listaIdentificadores ')' ';'
	| ESCRIBIR '(' listaExpresiones ')' ';'
	| IDENTIFICADOR ASIGNACION expresion ';' {asignarIdentificador($IDENTIFICADOR, $expresion);}
	| error ';'
	;
listaIdentificadores : IDENTIFICADOR {reedIdentificador($IDENTIFICADOR);}
	| listaIdentificadores ',' IDENTIFICADOR {reedIdentificador($IDENTIFICADOR);}
	;
listaExpresiones : expresion {writeIdentificador($expresion);}
	| listaExpresiones ',' expresion
	;
expresion: expresion '+' expresion  {$$ = hacerOperacion("ADD", $1, $3);}
	| expresion '-' expresion {$$ = hacerOperacion("SUBS", $1, $3);}
	| expresion '*' expresion {$$ = hacerOperacion("MULT", $1, $3);}
	| expresion '/' expresion {$$ = hacerOperacion("DIV", $1, $3);}
	| '(' expresion ')'
	| '-' expresion %prec NEG {$$ = hacerOperacion("INV", $1, "");}
	| IDENTIFICADOR 
	| CONSTANTE
	;

%%
