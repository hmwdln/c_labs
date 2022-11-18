#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void func_fill(int n, int m, int a[n][m])
{
    for (int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            a[i][j] = rand() % 40 - 20;
}

void print_matrix(int n, int m, int a[n][m])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
}

void func_transpose(int n, int m, int a[n][m], int t[m][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            t[j][i] = a[i][j];
        }
    }
}

void func_product(int n, int m, int a[n][m], int t[m][n], int p[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int sum = 0;
            for (int k = 0; k < m; k++)
                sum += a[i][k] * t[k][j];
            p[i][j] = sum;
        }
    }
}

int main()
{
    int n, m;
    printf("Введите размер матрицы: ");
    scanf("%d x %d", &n, &m);

    srand(time(NULL));

    int a[n][m];
    int t[m][n];
    int p[n][n];

    func_fill(n, m, a);
    print_matrix(n, m, a);
    printf("\n");
    func_transpose(n, m, a, t);
    print_matrix(m, n, t);
    printf("\n");
    func_product(n, m, a, t, p);
    print_matrix(n, n, p);

    return 0;
}