#include <stdio.h>
#include <stdlib.h>

typedef struct Grafo
{
    int ponderado;
    int num_vertices;
    int max_grau;
    int **arestas;
    int *grau;
} Grafo;

Grafo *gr;
int cont = 0;

void cria_grafo(int ponderado, int num_vertices, int max_grau)
{
    gr = (Grafo *)malloc(sizeof(Grafo));
    gr->ponderado = ponderado;
    gr->num_vertices = num_vertices;
    gr->max_grau = max_grau;
    gr->grau = (int *)calloc(num_vertices, sizeof(int));
    gr->arestas = (int **)malloc(num_vertices * sizeof(int *));
    for (int i = 0; i < num_vertices; i++)
    {
        gr->arestas[i] = (int *)malloc(max_grau * (sizeof(int *)));
    }
}

void libera_Grafo()
{
    if (gr != NULL)
    {
        int i;
        for (i = 0; i < gr->num_vertices; i++)
            free(gr->arestas[i]);
        free(gr->arestas);
        free(gr->grau);
        free(gr);
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

void busca_profundidade_r(int vertice, int *visitado)
{
    int i;
    visitado[vertice] = ++cont;
    for (i = 0; i < gr->grau[vertice]; i++)
    {
        if (!visitado[gr->arestas[vertice][i]])
        {
            busca_profundidade_r(gr->arestas[vertice][i], visitado);
        }
    }
}

void busca_profundidade(int vertice, int *visitado)
{
    int i;
    for (i = 0; i < gr->num_vertices; i++)
    {
        visitado[i] = 0;
    }
    busca_profundidade_r(vertice, visitado);
}

void busca_largura(int vertice, int *visitado)
{
    int i, vert, qtd_vertices, cont = 1, *fila, inicio_fila = 0, fim_fila = 0;
    for (i = 0; i < gr->num_vertices; i++)
    {
        visitado[i] = 0;
    }
    qtd_vertices = gr->num_vertices;
    fila = (int *)malloc(qtd_vertices * sizeof(int *));
    fim_fila++;
    fila[fim_fila] = vertice;
    visitado[vertice] = cont;
    while (inicio_fila != fim_fila)
    {
        inicio_fila = inicio_fila + 1;
        vert = fila[inicio_fila];
        cont++;
        for (i = 0; i < gr->grau[vert]; i++)
        {
            if (!visitado[gr->arestas[vert][i]])
            {
                fim_fila = fim_fila + 1;
                fila[fim_fila] = gr->arestas[vert][i];
                visitado[gr->arestas[vert][i]] = cont;
            }
        }
    }
    free(fila);
}

int menor_distancia(int *distancia, int *visitado, int num_vertices)
{
    int i, menor = -1, primeiro = 1;
    for (i = 0; i < num_vertices; i++)
    {
        if (distancia[i] >= 0 && visitado[i] == 0)
        {
            if (primeiro)
            {
                menor = i;
                primeiro = 0;
            }
            else
            {
                if (distancia[menor] > distancia[i])
                {
                    menor = i;
                }
            }
        }
    }
    return menor;
}

void dijkstra(int vertice, int *anterior, int *distancia)
{
    int i, num_vertices, contador, indice, *visitado, u;
    contador = num_vertices = gr->num_vertices;
    visitado = (int *)malloc(num_vertices * sizeof(int));
    for (i = 0; i < num_vertices; i++)
    {
        anterior[i] = -1;
        distancia[i] = -1;
        visitado[i] = 0;
    }
    distancia[vertice] = 0;
    while (cont > 0)
    {
        u = menor_distancia(distancia, visitado, num_vertices);
        if (u == -1)
        {
            break;
        }
        visitado[u] = 1;
        cont--;
        for (i = 0; i < gr->grau[u]; i++)
        {
            indice = gr->arestas[u][i];
            if (distancia[indice] < 0)
            {
                distancia[indice] = distancia[u] + 1;
                anterior[indice] = u;
            }
            else
            {
                if (distancia[indice] > distancia[u] + 1)
                {
                    distancia[indice] = distancia[u] + 1;
                    anterior[indice] = u;
                }
            }
        }
    }
    for (i = 0; i < num_vertices; i++)
    {
        printf("A distancia de %d a %d é %d\n", vertice, i, distancia[i]);
    }
    free(visitado);
}

int main()
{
    int digrafo = 1;
    int visita[5], anterior[5], distancia[5];
    cria_grafo(0, 5, 5);
    insere_aresta(0, 1, digrafo);
    insere_aresta(1, 3, digrafo);
    insere_aresta(1, 2, digrafo);
    insere_aresta(2, 4, digrafo);
    insere_aresta(3, 4, digrafo);
    insere_aresta(4, 1, digrafo);
    busca_profundidade(0, visita);
    for (int i = 0; i < 5; i++)
    {
        printf("O vértice %d foi visitado em %d lugar\n", i, visita[i]);
    }
    busca_largura(0, visita);
    for (int i = 0; i < 5; i++)
    {
        printf("O vértice %d foi visitado em %d lugar\n", i, visita[i]);
    }
    dijkstra(0, anterior, distancia);
    libera_Grafo();
}