#include <stdio.h>
#include <stdlib.h>

typedef struct Grafo
{
    int num_vertices;
    int max_grau;
    int **arestas;
    int *grau;
} Grafo;

Grafo *gr;

void cria_grafo(int num_vertices, int max_grau)
{
    gr = (Grafo *)malloc(sizeof(Grafo));
    gr->num_vertices = num_vertices;
    gr->max_grau = max_grau;
    gr->grau = (int *)calloc(num_vertices, sizeof(int));
    gr->arestas = (int **)malloc(num_vertices * sizeof(int *));
    for (int i = 0; i < num_vertices; i++)
    {
        gr->arestas[i] = (int *)malloc(max_grau * (sizeof(int *)));
    }
}

void insere_aresta(int vertice, int ligacao, int digrafo)
{
    gr->arestas[vertice][gr->grau[vertice]] = ligacao;
    gr->grau[vertice]++;
    if (!digrafo)
    {
        gr->arestas[ligacao][gr->grau[ligacao]] = vertice;
        gr->grau[ligacao]++;
    }
}

int main()
{
    int num_locais, juliano_total, qtd_pesquisa, qtd_vizinhos, juliano_passou, descobrir, vizinho;
    scanf("%d %d %d", &num_locais, &juliano_total, &qtd_pesquisa);
    cria_grafo(num_locais, num_locais);
    for (int i = 0; i < num_locais; i++)
    {
        scanf("%d", &qtd_vizinhos);
        for (int j = 0; j < qtd_vizinhos; j++)
        {
            scanf("%d", &vizinho);
            insere_aresta(i, vizinho, 1);
        }
    }
    int *visitado = calloc(num_locais, sizeof(int));
    for (int i = 0; i < juliano_total; i++)
    {
        scanf("%d", &juliano_passou);
        visitado[juliano_passou] = 1;
        for (int j = 0; j < gr->grau[juliano_passou]; j++)
        {
            visitado[gr->arestas[juliano_passou][j]] = 1;
        }
    }
    for (int i = 0; i < qtd_pesquisa; i++)
    {
        scanf("%d", &descobrir);
        if (visitado[descobrir])
        {
            printf("Eu vou estar la\n");
        }
        else
        {
            printf("Nao vou estar la\n");
        }
    }
    free(visitado);
    return 0;
}