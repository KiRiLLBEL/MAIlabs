#include <stdio.h>
#include "string.h"
#include "stack.h"
bool isInt(const char *str) {
    while(*str)  {
        if((*str< '0' || *str > '9') && *str != '-' && *str != '.')
            return false;
        str++;
    }
    return true;
}
int main() {
    stack * a = malloc(sizeof(stack));
    CreateStack(a);
    bool ProgramDo = true;
    while (ProgramDo) {
        printf("1. Push Stack\n2. Pop Stack\n3. Print Stack\n4. Merge Sort\n5. Exit\n");
        char inputString[9] = "";
        int switcher;
        scanf("%s", inputString);
        if(!strcmp("1",inputString)){
            switcher = 1;
        }
        else if(!strcmp("2", inputString)) {
            switcher = 2;
        }
        else if(!strcmp("3", inputString)) {
            switcher = 3;
        }
        else if(!strcmp("4", inputString)) {
            switcher = 4;
        }
        else if(!strcmp("5", inputString)) {
            switcher = 5;
        }else {
            printf("Error, incorrect input\n");
        }
        if (switcher == 1) {
            char inputNumber[9] = "";
            int pushElement;
            bool ElementIsInt = true;
            while (ElementIsInt) {
                printf("Input new element of stack\n");
                scanf("%s", inputNumber);
                if (isInt(inputNumber)){
                    pushElement = strtol(inputNumber, NULL, 10);
                    ElementIsInt = false;
                } else {
                    printf("Error, is not number\n");
                }
            }
            PushStack(a, pushElement);
        }
        else if (switcher == 2) {
            if (!EmptyStack(a)) {
                system("clear");
                printf("Top element of Stack = %d\n", TopStack(a));
                PopStack(a);
            }
            else {
                printf("Error stack is over, please add element\n");
                char inputNumber[9] = "";
                int pushElement;
                bool ElementIsInt = true;
                while (ElementIsInt) {
                    printf("Input new element of stack\n");
                    scanf("%s", inputNumber);
                    if (isInt(inputNumber)){
                        pushElement = strtol(inputNumber, NULL, 10);
                        ElementIsInt = false;
                    } else {
                        printf("Error, is not number\n");
                    }
                }
                PushStack(a, pushElement);
            }
        }
        else if (switcher == 3) {
            if (!EmptyStack(a)) {
                stack * b = malloc(sizeof(stack));
                stack * c = malloc(sizeof(stack));
                CreateStack(b);
                CreateStack(c);
                while (!EmptyStack(a)) {
                    PushStack(b, TopStack(a));
                    PushStack(c, TopStack(a));
                    PopStack(a);
                }
                ReverseStack(b);
                ReverseStack(c);
                DestroyStack(a);
                free(a);
                a = c;
                system("clear");
                while (!EmptyStack(b)) {
                    printf("%d ", TopStack(b));
                    PopStack(b);
                }
                printf("\n");
                DestroyStack(b);
                free(b);
            } else {
                printf("Error stack is over, please add element\n");
                char inputNumber[9] = "";
                int pushElement;
                bool ElementIsInt = true;
                while (ElementIsInt) {
                    printf("Input new element of stack\n");
                    scanf("%s", inputNumber);
                    if (isInt(inputNumber)) {
                        pushElement = strtol(inputNumber, NULL, 10);
                        ElementIsInt = false;
                    } else {
                        printf("Error, is not number\n");
                    }
                }
                PushStack(a, pushElement);
            }
        }
        else if (switcher == 4) {
            if (!EmptyStack(a)) {
                a = MergeSortStack(a, 0, SizeStack(a));
                stack * b = malloc(sizeof(stack));
                stack * c = malloc(sizeof(stack));
                CreateStack(b);
                CreateStack(c);
                while (!EmptyStack(a)) {
                    PushStack(b, TopStack(a));
                    PushStack(c, TopStack(a));
                    PopStack(a);
                }
                ReverseStack(b);
                ReverseStack(c);
                DestroyStack(a);
                free(a);
                a = c;
                system("clear");
                while (!EmptyStack(b)) {
                    printf("%d ", TopStack(b));
                    PopStack(b);
                }
                printf("\n");
                DestroyStack(b);
                free(b);
            }
            else {
                printf("Error stack is over, please add element\n");
                char inputNumber[9] = "";
                int pushElement;
                bool ElementIsInt = true;
                while (ElementIsInt) {
                    printf("Input new element of stack\n");
                    scanf("%s", inputNumber);
                    if (isInt(inputNumber)) {
                        pushElement = strtol(inputNumber, NULL, 10);
                        ElementIsInt = false;
                    } else {
                        printf("Error, is not number\n");
                    }
                }
                PushStack(a, pushElement);
            }
        }
        if (switcher == 5) {
            system("clear");
            printf("Exit\n");
            ProgramDo = false;
        }
    }
    DestroyStack(a);
    return 0;
}
