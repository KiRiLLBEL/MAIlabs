#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int abs(int a) 
{
    if (a >= 0) {
        return a;
    } else {
        return (-1 * a);
    }
}

int max(int a, int b) 
{
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int sign(int a) 
{
    if (a < 0) {
        return -1;
    }
    if (a == 0) {
        return 0;
    } else {
        return 1;
    }
}

int min(int a, int b) 
{
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

int mod(int a, int b) 
{
    return abs(a) % abs(b);
}
int main(void) 
{
    int i0;
    int j0;
    int l0;
    scanf("%d%d%d", &i0, &j0, &l0);
    int i = i0;
    int j = j0;
    int l = l0;
    int iLast;
    int jLast;
    int lLast;
    for (int k = 0; k < 50; ++k) {
        iLast = i;
        jLast = j;
        lLast = l;
        i = max(min(iLast + jLast - lLast - k, iLast - jLast + lLast - k), min(k + iLast - jLast - lLast, k - iLast - jLast + lLast));
        j = jLast + mod(lLast * sign(jLast), 20) + mod(k * sign(iLast), 10);
        l = abs(iLast - jLast + lLast - k) * sign(iLast) * sign(jLast);
        if (((i - 10) * (i - 10) + (j - 10) * (j - 10) <= 100) && ((i - 10) * (i - 10) + (j - 10) * (j - 10) >= 25)) {
            printf("Yes\n %d %d %d %d", i, j, l, k);
            return 0;
        }
    }
    printf("No\n%d %d %d %d\n", i, j, l, 50);
    return 0;
}