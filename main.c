#include <stdio.h>
#include <stdlib.h>
#include <String.h>
#include <time.h>
#include "grafolista.h"
#include "Lista.h"

#define AZUL 1
#define AMARELO 2
#define VERDE 3
#define VERMELHO 4

typedef struct resposta{
    char nome[100];
    int cor;
    int possibilidades[4];
    int grau;
} Resposta;

int checarCompativel(No *ini, int cor, Resposta *vet_assignment, int atual, int tamanho)
{
    char aux[100];
    int i;
    if(ini == NULL)
        return 1;
    while(ini != NULL)
    {
        strcpy(aux, ini->nome);
        for(i = 0; i < tamanho; i++)
        {
            if(strcmp(aux, vet_assignment[i].nome) == 0)
            {
                if(vet_assignment[i].cor == cor)
                    return 0;
            }
        }
        ini = ini->prox;
    }
    return 1;
}

int checarResposta(Resposta *vetor, int tamanho)
{
    int i;
    for(i = 0; i < tamanho; i++)
    {
        if(vetor[i].cor == 0)
            return 0;
    }
    return 1;
}

void imprimir_resposta(Resposta *vetor, int tamanho)
{
    int i;
    for(i = 0; i < tamanho; i++)
    {
        printf("%s: ", vetor[i].nome);
        if(vetor[i].cor == AZUL)
            printf("Azul.\n");
        else if(vetor[i].cor == VERDE)
            printf("Verde.\n");
        else if(vetor[i].cor == VERMELHO)
            printf("Vermelho.\n");
        else if(vetor[i].cor == AMARELO)
            printf("Amarelo.\n");
    }
}

int verificarAdiante(Resposta *vet_assignment, int tamanho)
{
    int i;
    for(i = 0; i < tamanho; i++)
    {
        if(vet_assignment[i].possibilidades[0] != 1 && vet_assignment[i].possibilidades[1] != 1 &&
           vet_assignment[i].possibilidades[2] != 1 && vet_assignment[i].possibilidades[3] != 1)
        {
            return 0;
        }
    }
    return 1;
}

void atualizarVerificacaoAdiante(No *ini, int index, Resposta *vet_assignment, int atual, int tamanho)
{
    char aux[100];
    int i;
    vet_assignment[atual].possibilidades[0] = 0;
    vet_assignment[atual].possibilidades[1] = 0;
    vet_assignment[atual].possibilidades[2] = 0;
    vet_assignment[atual].possibilidades[3] = 0;
    vet_assignment[atual].possibilidades[index] = 1;
    while(ini != NULL)
    {
        strcpy(aux, ini->nome);
        for(i = 0; i < tamanho; i++)
        {
            if(strcmp(aux, vet_assignment[i].nome) == 0)
                vet_assignment[i].possibilidades[index] = 0;
        }
        ini = ini->prox;
    }
}

void voltarAtualizacao(No *ini, int index, Resposta *vet_assignment, int tamanho)
{
    char aux[100];
    int i;
    while(ini != NULL)
    {
        strcpy(aux, ini->nome);
        for(i = 0; i < tamanho; i++)
        {
            if(strcmp(aux, vet_assignment[i].nome) == 0 && vet_assignment[i].cor == 0)
                vet_assignment[i].possibilidades[index] = 1;
        }
        ini = ini->prox;
    }
}

int MVR(Resposta *vet_assignment, int tamanho)
{
    int menor = 5, valor, i, retorno;
    for(i = 0; i < tamanho; i++)
    {
        valor = vet_assignment[i].possibilidades[0] + vet_assignment[i].possibilidades[1] + vet_assignment[i].possibilidades[2] +
        vet_assignment[i].possibilidades[3];
        if(vet_assignment[i].cor == 0 && menor > valor)
        {
            retorno = i;
            menor = valor;
        }
    }
    return retorno;
}

int MVRGrau(Resposta *vet_assignment, int tamanho)
{
    int menor = 5, valor, i, retorno;
    for(i = 0; i < tamanho; i++)
    {
        valor = vet_assignment[i].possibilidades[0] + vet_assignment[i].possibilidades[1] + vet_assignment[i].possibilidades[2] +
        vet_assignment[i].possibilidades[3];
        if(vet_assignment[i].cor == 0 && menor > valor)
        {
            retorno = i;
            menor = valor;
        }
        else if(vet_assignment[i].cor == 0 && menor == valor && vet_assignment[i].grau > vet_assignment[retorno].grau)
        {
            retorno = i;
        }
    }
    return retorno;
}

int colorir(LGrafo *g, Resposta *vet_assignment, int atual, int tamanho, char tipo)
{
    int i, prox;
    int aux[4];
    contador++;
    if(checarResposta(vet_assignment, tamanho) == 1)
        return 1;
    else if(tipo != 'a' && verificarAdiante(vet_assignment, tamanho) == 0)
        return 0;
    for(i = 1; i < 5; i++)
    {
        if(checarCompativel(g->lista[atual].ini, i, vet_assignment, atual, tamanho) == 1)
        {
            vet_assignment[atual].cor = i;
            if(tipo != 'a')
            {
                aux[0] = vet_assignment[atual].possibilidades[0];
                aux[1] = vet_assignment[atual].possibilidades[1];
                aux[2] = vet_assignment[atual].possibilidades[2];
                aux[3] = vet_assignment[atual].possibilidades[3];
                atualizarVerificacaoAdiante(g->lista[atual].ini, i - 1, vet_assignment, atual, tamanho);
            }
            if(tipo == 'a' || tipo == 'b')
                prox = atual + 1;
            if(tipo == 'c')
                prox = MVR(vet_assignment, tamanho);
            if(tipo == 'd')
                prox = MVRGrau(vet_assignment, tamanho);
            if(colorir(g, vet_assignment, prox, tamanho, tipo) == 1)
            {
                return 1;
            }
            else
            {
                if(tipo != 'a')
                {
                    vet_assignment[atual].possibilidades[0] = aux[0];
                    vet_assignment[atual].possibilidades[1] = aux[1];
                    vet_assignment[atual].possibilidades[2] = aux[2];
                    vet_assignment[atual].possibilidades[3] = aux[3];
                    voltarAtualizacao(g->lista[atual].ini, i - 1, vet_assignment, tamanho);
                }
                vet_assignment[atual].cor = 0;
            }
        }
    }
    return 0;
}

int main()
{
    LGrafo g;
    int i, tamanho;
    char tipo, c;
    char aux[100];
    Resposta *vet_assignment;
    scanf("%d %c", &tamanho, &tipo);
    getchar();

    Lcriar_grafo(&g, tamanho);
    vet_assignment = (Resposta *) malloc(sizeof(Resposta) * tamanho);
    for(i = 0; i < tamanho; i++)
    {
        vet_assignment[i].cor = 0;
        vet_assignment[i].grau = 0;
        vet_assignment[i].possibilidades[0] = 1;
        vet_assignment[i].possibilidades[1] = 1;
        vet_assignment[i].possibilidades[2] = 1;
        vet_assignment[i].possibilidades[3] = 1;
    }
    for(i = 0; i < tamanho; i++)
    {
        scanf("%[^:]", aux);
        getchar();
        getchar();
        strcpy(vet_assignment[i].nome, aux);
        while(1)
        {
            scanf("%[^,^.]", aux);
            getchar();
            Linserir_aresta(&g, i, aux);
            vet_assignment[i].grau++;
            if(getchar() == '\n')
            {
                break;
            }
        }
    }
    if(colorir(&g, vet_assignment, 0, tamanho, tipo) == 1)
        imprimir_resposta(vet_assignment, tamanho);
    return 0;
}
