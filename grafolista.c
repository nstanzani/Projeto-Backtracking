#include "grafolista.h"
#include "Lista.h"
#include <stdlib.h>
#include <stdio.h>

int Lcriar_grafo(LGrafo *g, int n)
{
    int i;
    g->lista = (Lista *) malloc(n * sizeof(Lista));
    for(i = 0; i < n; i++)
        inilista(&(g->lista[i]));
    g->n = n;
    return SUCCESS;
}

int Linserir_aresta(LGrafo *g, int l, char *c)
{
    inserirlista(&(g->lista[l].ini), c);
    return SUCCESS;
}

int Limprimir_grafo(LGrafo *g)
{
    int i;
    if(g == NULL || g->lista == NULL)
        return INVALID_ARGUMENT;
    for(i = 0; i < g->n; i++)
    {
        printf("%d: ", i);
        imprimelista(g->lista[i].ini);
        printf("\n");
    }
    return SUCCESS;
}
