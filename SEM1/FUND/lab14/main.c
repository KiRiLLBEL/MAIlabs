#include <stdio.h>

int main(void)
{
    int n;
    int t;
    scanf("%d %d", &t, &n);
    int arr[n][n];
    
    for (int k = 0; k < t; k++) {
        int m;
        scanf("%d", &m);
        int s = 1;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d", &arr[i][j]);
            }
        }
        while (s <= m) {
            for (int i = m - 1; i >= m - s; i--) {
                printf("%d ", arr[i][2 * (m - 1) - s + 1 - i]);
            }
            s++;
        }
        s = 2;
        while (s <= m) {
            for (int i = m - s; i >= 0; i--) {
                printf("%d ", arr[i][m - s - i]);
            }
            s++;
        }
        printf("\n");
    }
    return 0;
}