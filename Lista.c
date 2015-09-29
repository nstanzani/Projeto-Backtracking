#include "Lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <String.h>

void inilista(Lista *l)
{
    l->ini = NULL;
}

int inserirlista(No **ini, char* nome)
{
    No *aux = (No *) malloc(sizeof(No));
    No *aux2 = NULL;
    if(aux == NULL)
        return OUT_OF_MEMORY;
    strcpy(aux->nome, nome);
    aux->prox = NULL;
    if((*ini) == NULL)
    {
        (*ini) = aux;
        return SUCCESS;
    }
    aux2 = (*ini);
    while(aux2->prox != NULL)
        aux2 = aux2->prox;
    aux2->prox = aux;
    return SUCCESS;
}

int imprimelista(No *ini)
{
    if(ini == NULL)
        return INVALID_ARGUMENT;
    while(ini != NULL)
    {
        if(ini->prox == NULL)
            printf("%s.", ini->nome);
        else
            printf("%s, ", ini->nome);
        ini = ini->prox;
    }
    return SUCCESS;
}
