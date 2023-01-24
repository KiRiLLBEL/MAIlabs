#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int partition(int * vec, int l, int r) {
    int v = vec[(l + r) / 2];
    int i = l;
    int j = r;
    while(i <= j) {
        while(vec[i] < v)
            i++;
        while(vec[j] > v)
            j--;
        if(i >= j)
            break;
        int w = vec[i];
        vec[i++] = vec[j];
        vec[j--] = w;
    }
    return j;
}
void quicksort(int * vec, int l, int r) {
    if(l < r) {
        int q = partition(vec, l, r);
        quicksort(vec, l, q);
        quicksort(vec, q + 1, r);
    }
}

int main() {
    clock_t start;
    clock_t end;
    int n;
    scanf("%d", &n);
    int * vec = calloc(n, sizeof(int));
    for (int i = 0; i < n; ++i) {
        scanf("%d", &vec[i]);
    }
    start = clock();
    quicksort(vec, 0, n - 1);
    end = clock();
    for (int i = 0; i < n; ++i)
    {
        printf("%d ", vec[i]);
    }
    printf("\n");
    printf("Time: %lf\n", (double)(end - start)/CLOCKS_PER_SEC);
}