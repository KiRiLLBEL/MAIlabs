#include <stdio.h>
#include <math.h>
long long modul(long long x) {
    if (x >= 0) {
        return x;
    } else {
        return x * -1;
    }
}
int main(void) 
{
    long long x;
    while (scanf("%lld", &x) != EOF) {
        long long t = 0;
        if (x < 0) {
            x = modul(x);
            t = 1;
        }
        long long l = 0;
        long long d = x;
        while (d > 0) {
            d = d / 10;
            l++;
        }
        if (l % 2 == 0) {
            long long s = 0;
            long long k = 0;
            while (x > 0) {
                long long a = x % 10;
                x = x / 10;
                long long b = x % 10;
                x = x / 10;
                s += (modul(b - a) * 100 + b * 10 + a) * powl(1000, k);
                k++;
            }
            if (t == 0) {
                printf("%lld\n", s);
            } else {
                printf("-%lld\n", s);
            }
        } else {
            long long s = 0;
            long long k = 0;
            while (x > 10) {
                long long a = x % 10;
                x = x / 10;
                long long b = x % 10;
                x = x / 10;
                s += (modul(b - a) * 100 + b * 10 + a) * powl(1000, k);
                k++;
            }
            s += x * powl(1000, k);
            if (t == 0) {
                printf("%lld\n", s);
            } else {
                printf("-%lld\n", s);
            }
        }
    }
    return 0;
}