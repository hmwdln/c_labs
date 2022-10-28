#include <stdio.h>
#include <math.h>

f(int n)
{
    double pi1, h, x, integral;
    pi1 = M_PI / 2;
    h = pi1 / n;
    for (x = pi1 / n; x <= M_PI; x += h)
    {
        double fun;
        if (x <= pi1)
            fun = pow(2, x) - 2 + pow(x, 2);
        else
            fun = sqrt(x) * exp(-pow(x, 2));
        integral += fun
    }
}

int main()
{
    /* if (0 <= x && x <= (M_PI / 2))
        f = pow(2, x) - 2 + pow(x, 2);
    else if ((M_PI / 2) < x && x <= M_PI)
        f = sqrt(x) * exp(-pow(x, 2));
        printf("x = %lf\t f(x) = %lf\n", x, f); */
}