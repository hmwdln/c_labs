#include <stdio.h>
#include <math.h>

double f(int n)
{
    double pi1, h, x, integral = 0;
    pi1 = M_PI / 2;
    h = M_PI / n;
    for (x = pi1 / n; x <= M_PI; x += h)
    {
        double fun;
        if (x <= pi1)
            fun = pow(2, x) - 2 + pow(x, 2);
        else
            fun = sqrt(x) * exp(-pow(x, 2));
        integral += fun;
    }
    integral *= h;
    return integral;
}

int main()
{
    double e;
    printf("Введите точность => ");
    scanf("%lf", &e);
    int n = 1;
    double integral_1 = 0;
    double integral_2 = 1;
    while ((fabs(integral_2 - integral_1) / 3) >= e)
    {
            n *= 2;
            integral_1 = integral_2;
            integral_2 = f(n * 2);
    }
    printf("%lf\n", integral_2);
    return 0;
}