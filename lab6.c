#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void func_fill(int n, int a[])
{
    int i;
    for (i = 0; i < n; i++)
        a[i] = rand () % 20 - 10;
}

int func_sum(int r, int g, int a[])
{
    int sum = 0;
    for (int i = r; i <= g; i++)
        sum += a[i];
    return sum;
}

int func_product(int r, int g, int a[])
{
    int product = 1;
    for (int i = r; i <= g; i++)
        product *= a[i];
    return product;
}

int func_same(int r, int a[], int s)
{
    for (int i = r + 1; i < s; i++)
        if (a[r] == a[i])
            return i;
    return -1;
}

void print_a(int size, int a[])
{
    for (int i = 0; i < size; i++)
        printf("%d ", a[i]);
}

int main()
{
    srand(time(NULL));
    int size;
    printf("Введите размер массива: ");
    scanf("%d", &size);
    int a[size];
    func_fill(size, a);
    printf("Исходный массив: ");
    print_a(size, a);
    printf("\n");

    int sum, product, first_number, last_number;
    for (int i = 0; i < size; i++)
    {
        first_number = i;
        last_number = func_same(i, a, size);
        if (last_number != -1)
            break;
    }

    sum = func_sum(first_number, last_number, a);
    product = func_product(first_number, last_number, a);
    a[first_number] = sum;
    a[last_number] = product;

    if (last_number == -1)
        printf("Повторяющиеся элементы не найдены\n");
    else
    {
        printf("Повторяющиеся элементы: %d и %d.\n", first_number, last_number);
        printf("Сумма элементов: %d.\n", sum);
        printf("Произведение элементов: %d.\n", product);
        print_a(size, a);
        printf("\n");
    }
}