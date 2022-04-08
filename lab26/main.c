#include <stdio.h>
#include "stack.h"
int main() {
    stack * a = malloc(sizeof(stack));
    CreateStack(a);
    PushStack(a, 10);
    PushStack(a, 2);
    PushStack(a, 5);
    PushStack(a, 1);
    PushStack(a, 9);
    PushStack(a, 7);
    a = MergeSortStack(a, 0, SizeStack(a));
    int size = SizeStack(a);
    for (int i = 0; i != size; ++i) {
        printf("%d ", TopStack(a));
        PopStack(a);
    }
    DestroyStack(a);
    free(a);
    return 0;
}
