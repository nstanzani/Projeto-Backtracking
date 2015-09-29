#ifndef GRAFOLISTA_H
#define GRAFOLISTA_H

#include "Lista.h"
#define SUCCESS 0
#define INVALID_ARGUMENT 1
#define OUT_OF_MEMORY 2
#define FALSE -1
#define BRANCO -4
#define CINZA -5
#define PRETO -6

typedef struct lgrafo
{
    Lista *lista;
    int n;
} LGrafo;

int Lcriar_grafo(LGrafo *g, int n);

int Linserir_aresta(LGrafo *g, int l, char *c);

int Limprimir_grafo(LGrafo *g);

#endif // GRAFOLISTA_H
