#include <stdio.h>

int main(void)
{
    long long n;
    long long t;
    scanf("%lld %lld", &t, &n);
    long long arr[n][n];
    for (long long k = 0; k < t; k++) {
        long long m;
        scanf("%lld", &m);
        for (long long i = 0; i < m; i++) {
            for (long long j = 0; j < m; j++) {
                scanf("%lld", &arr[i][j]);
            }
        }
        for (long long i = 0; i < m; i++) {
            long long Sum = 0;
            long long icyc = i + 1;
            long long jcyc = (m - 1 - i) + 1;
            while (icyc < m && jcyc < m) {
                Sum += arr[icyc][jcyc];
                icyc++;
                jcyc++;
            }
            icyc = i;
            jcyc = (m - 1 - i);
            while (icyc >= 0 && jcyc >= 0) {
                Sum += arr[icyc][jcyc];
                icyc--;
                jcyc--;
            }
            arr[i][(m - 1 - i)] = Sum;
        }
        for (long long i = 0; i < m; i++) {
            for (long long j = 0; j < m; j++) {
                printf("%lld ", arr[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}