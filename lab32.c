#include <stdio.h>
#include <math.h>
int main()
{
    double h;
    printf("Enter h (0, 3] = ");
    scanf("%lf", &h);
    unsigned int a = 3 / h;
    double f;
    for (int i = 0; i <= a; i++)
    {
        double x = i*h;
        if (1.5 < x && x <= 3.0)
            f = pow(2, x) - 2 + pow(x, 2);
        else
            f = exp(-x - (1 / x));
          printf("x = %lf\t f(x) = %lf\n", x, f);
    }
    return 0;
}
