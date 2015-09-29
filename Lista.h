#ifndef LISTA_H
#define LISTA_H

#define SUCCESS 0
#define INVALID_ARGUMENT 1
#define OUT_OF_MEMORY 2
#define FALSE -1

typedef struct celula
{
    char nome[100];
    struct celula *prox;
} No;

typedef struct lista
{
    No *ini;
} Lista;

void inilista(Lista *l);
int inserirlista(No **ini, char *nome);
int imprimelista(No *ini);

#endif // LISTA_H
