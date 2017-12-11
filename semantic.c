#include <stdio.h>
#include <stdlib.h>
#include "symbol.h"
#include "scanner.h"
#include "parser.h"
extern int semanticErrs;
int variblesTemp = 0;

void definirIdentificador(char *nuevoIdentificador)
{
    if(estaDefinido(nuevoIdentificador) != NULL)
    {
        char str[60];
        printf("Llegaste aca\n");
        sprintf(str,"Error semantico: identificador %s ya declarado\n", nuevoIdentificador);
        yyerror(str);
        semanticErrs++;
    }
    else
    {
        printf("Declare %s,Integer\n", nuevoIdentificador);
        push(identificadoresDefinidos, nuevoIdentificador);
    }
}

int invocarIdentificador(char *nuevoIdentificador)
{
    struct elem *aux = estaDefinido(nuevoIdentificador);
    if(aux != NULL)
    {
        char str[60];
        sprintf(str,"Error Semantico: variable no definida: %s\n", nuevoIdentificador);
        yyerror(str);
        semanticErrs++;
        return 1;
    }
    return 0;
}

char *hacerOperacion(char *operador, char *exp1, char *exp2)
{
    char *aux; 
    aux = (char*)malloc(30);
    variblesTemp++;
    sprintf(aux, "Temp#%d", variblesTemp);
    definirIdentificador(aux);
    printf("%s %s,%s,%s\n", operador, exp1, exp2, aux);
    return aux;
}

void writeIdentificador(char *identificador)
{
    printf("Write %s,Integer\n", identificador);
}

void reedIdentificador(char *identificador)
{
    if(invocarIdentificador(identificador) != 1) printf("Reed %s,Integer\n", identificador);
}

void asignarIdentificador(char *identificador, char *valor)
{
    if(invocarIdentificador(identificador) != 1) printf("Store %s,%s\n", valor, identificador);
}

void load()
{
    printf("Load rtlib,\n");
}

void stop()
{
    printf("Stop ,\n");
}
