#include <stdio.h>
#include <stdlib.h>

void chuva(int **matriz, int vertice, int grau, int anterior)
{
    for (int i = 1; i < grau; i++)
    {
        for (int j = 0; j < grau; j++)
        {
            if (matriz[i][j] == -1)
            {
                if ((matriz[i - 1][j] == 1) ||
                    (j + 1 < grau && i + 1 < grau && j > 0 && matriz[i][j - 1] == 1 && matriz[i + 1][j - 1] == 0) ||
                    (j + 1 < grau && i + 1 < grau && matriz[i][j + 1] == 1 && matriz[i + 1][j + 1] == 0))
                {
                    matriz[i][j] = 1;
                }
            }
        }
    }
}

int main()
{
    int linhas, colunas, j;
    scanf("%d %d", &linhas, &colunas);
    int **parede = (int **)malloc(linhas * sizeof(int));
    for (int i = 0; i < linhas; i++)
    {
        parede[i] = (int *)malloc(linhas * sizeof(int *));
    }
    for (int i = 0; i < linhas; i++)
    {
        for (j = 0; j < colunas; j++)
        {
            scanf("%d", &parede[i][j]);
        }
    }
    chuva(parede, 0, colunas, 0);
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            printf("%d ", parede[i][j]);
        }
        printf("\n");
    }
}