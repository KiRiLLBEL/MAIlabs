#include <stdio.h>
#include "string.h"
#include "stack.h"
int main() {
    stack * a = malloc(sizeof(stack));
    CreateStack(a);
    bool ProgramDo = true;
    printf("Creating stack...\n");
    while (ProgramDo) {
        printf("input value\n");
        int x = 0;
        scanf("%d", &x);
        PushStack(a, x);
        printf("Continue?\n");
        char input[] = "\0";
        bool inputDo = true;
        while (inputDo) {
            scanf("%s", input);
            if (strcmp(input, "yes") == 0) {
                ProgramDo = true;
                inputDo = false;
            }
            else if(strcmp(input, "no") == 0) {
                ProgramDo = false;
                inputDo = false;
            }
            else {
                printf("Incorrect input, please retry");
                inputDo = true;

            }
        }
    }
    a = MergeSortStack(a, 0, SizeStack(a));
    int size = SizeStack(a);
    for (int i = 0; i != size; ++i) {
        if (EmptyStack(a) == 1) {
            printf("Error, stack is over");
            break;
        }
        else {
            printf("%d ", TopStack(a));
            PopStack(a);
        }
    }
    DestroyStack(a);
    free(a);
    return 0;
}
