#include <stdio.h>
#include <math.h>

int main()
{
    double f, h, x;
    unsigned int a, c = 0;
    printf("Введите шаг h - (0, 3): ");
    scanf("%lf", &h);
    a = 3 / h;
    while (c <= a)
    {
        if (0 <= x && x <= 1.5)
            f = pow(2, x) - 2 + pow(x, 2);
        else
            f = sqrt(x) * exp(-pow(x, 2));
        printf("x = %lf\t f(x) = %lf\n", x, f);
        x += h;
        c += 1;
    }
    return 0;
}
