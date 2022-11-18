#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void func_fill(int n, int m, int *a)
{
    for (int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            a[i * m + j] = rand() % 40 - 20;
}

void print_matrix(int n, int m, int *a)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%d ", a[i * m + j]);
        printf("\n");
    }
}

void func_transpose(int n, int m, int *a, int *t)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            t[j * n + i] = a[i * m + j];
        }
    }
}

void func_product(int n, int m, int *a, int *t, int *p)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int sum = 0;
            for (int k = 0; k < m; k++)
                sum += a[i * m + k] * t[k * n + j];
            p[i * n + j] = sum;
        }
    }
}

int main()
{
    int n, m;
    printf("Введите размер матрицы: ");
    scanf("%d x %d", &n, &m);

    srand(time(NULL));

    int *a = malloc(n * m * sizeof(int));
    int *t = malloc(m * n * sizeof(int));
    int *p = malloc(n * n * sizeof(int));

    if (NULL == p || NULL == a || NULL == t)
    {
        printf("Не удалось выделить память!\n");
        exit(EXIT_FAILURE);
    }

    func_fill(n, m, a);
    printf("Исходная матрица: \n");
    print_matrix(n, m, a);
    printf("\n");
    func_transpose(n, m, a, t);
    printf("Транспонированная матрица: \n");
    print_matrix(m, n, t);
    printf("\n");
    func_product(n, m, a, t, p);
    printf("Произведение матриц: \n");
    print_matrix(n, n, p);

    free(a);
    free(t);
    free(p);

    return 0;
}