#include <stdio.h>
#include <stdlib.h>

void chuva(int **matriz, int grau, int coluna)
{
    for (int i = 1; i < grau; i++)
    {
        for (int j = 0; j < coluna; j++)
        {
            if (matriz[i][j] == -1)
            {
                if ((matriz[i - 1][j] == 1) ||
                    (j + 1 < coluna && i + 1 < grau && j > 0 && matriz[i][j - 1] == 1 && matriz[i + 1][j - 1] == 0) ||
                    (j + 1 < coluna && i + 1 < grau && matriz[i][j + 1] == 1 && matriz[i + 1][j + 1] == 0))
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
    char c;
    for (int i = 0; i < linhas; i++)
    {
        parede[i] = (int *)malloc(colunas * sizeof(int *));
    }
    for (int i = 0; i < linhas; i++)
    {
        for (j = 0; j < colunas; j++)
        {
            scanf(" %c", &c);
            if (c == '.')
            {
                parede[i][j] = -1;
            }
            else if (c == 'o')
            {
                parede[i][j] = 1;
            }
            else
            {
                parede[i][j] = 0;
            }
            // scanf(" %c", &parede[i][j]);
        }
    }
    chuva(parede, linhas, colunas);
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {

            if (parede[i][j] == -1)
            {
                printf(".");
            }
            else if (parede[i][j] == 1)
            {
                printf("o");
            }
            else
            {
                printf("#");
            }
            // printf("%d ", parede[i][j]);
        }
        printf("\n");
    }
}