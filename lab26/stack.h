#ifndef STACK_H
#define STACK_H
#include "stdlib.h"
#include "stdbool.h"
#include "stdio.h"
struct ItemStack {
    int data;
    struct ItemStack * prev;
};
typedef struct {
    struct ItemStack * top;
    int size;
} stack;
void CreateStack(stack * s);
bool EmptyStack(stack * s);
int SizeStack(stack * s);
bool PushStack(stack * s, int t);
bool PopStack(stack * s);
int TopStack(stack * s);
void DestroyStack(stack * s);
void ReverseStack(stack * s);
void MergeStack(stack *c, stack * a, stack * b);
stack * MergeSortStack(stack * s, int left, int right);
#endif