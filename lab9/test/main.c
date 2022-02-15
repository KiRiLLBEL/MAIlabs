#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int divs(double a, double b)
{
    double c;
    c = a / b;
    return floor(c);
}

int mod(int a, int b)
{
    return a - divs(a, b) * b;
}

int main(void)
{
    int x,y;
    scanf("%d%d", &x, &y);
    printf("%d %d", mod(x, y), divs(x, y));
    return 0;
}
