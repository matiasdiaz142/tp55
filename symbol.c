#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct elem
{
    char *nombre;
    struct elem *siguiente;
};



struct elem *identificadoresDefinidos = NULL;

struct elem *estaDefinido(char *nuevoIdentificador)
{
    struct elem *aux = identificadoresDefinidos;
    while(identificadoresDefinidos != NULL)
    {
        if(strcmp(aux->nombre, nuevoIdentificador) == 0 )
        {
            //Esta definido
            return aux;
        }
        aux = aux->siguiente;
    }
    //No esta definido
    return NULL;
}

void push(struct elem *pila, char *identificador)
{
    struct elem *aux;
    aux =(struct elem *)malloc(sizeof(struct elem));
    aux->nombre = identificador;
    aux->siguiente = pila;
    pila = aux;
}