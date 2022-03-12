#include <stdio.h>
#include "stdlib.h"
#include "stdbool.h"
#include "queue.h"
int main() {
    queue q;
    Create(&q);
    Push(&q, 10);
    Push(&q, 13);
    Push(&q, 14);
    printf("%d ", Top(&q));
    Pop(&q);
    printf("%d ", Top(&q));
    Destroy(&q);
    int * x = 10;
    printf("%d %d", x, *x);
    return 0;
}
