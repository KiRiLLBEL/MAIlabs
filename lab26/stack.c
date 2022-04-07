#include "stack.h"
void CreateStack(stack * s){
    s->top = 0;
    s->size = 0;
}
bool EmptyStack(stack * s) {
    return s->top == 0;
}
int SizeStack(stack * s) {
    return s->size;
}
bool PushStack(stack * s, int t) {
    struct ItemStack * i = malloc(sizeof(struct ItemStack));
    if (!i)
        return false;
    i->data = t;
    i->prev = s->top;
    s->top = i;
    s->size++;
    return true;
}
bool PopStack(stack * s) {
    if(!s->size)
        return  false;
    struct ItemStack * i = s->top;
    s->top = s->top->prev;
    s->size--;
    free(i);
    return true;
}
int TopStack(stack * s) {
    if(s->top)
        return s->top->data;
}
void DestroyStack(stack * s) {
    while (s->top) {
        struct ItemStack * i = s->top;
        s->top = s->top->prev;
        free(i);
    }
    s->top = 0;
    s->size = 0;
}
void ReverseStack(stack * s) {
    stack r;
    CreateStack(&r);
    while (!EmptyStack(s)) {
        PushStack(&r, TopStack(s));
        PopStack(s);
    }
    DestroyStack(s);
    *s = r;
}
void MergeStack(stack *c, stack * a, stack * b) {
    while (!EmptyStack(a) || !EmptyStack(b)) {
        if (EmptyStack(a) == 0 && EmptyStack(b) == 0 && (TopStack(a) < TopStack(b))){
            PushStack(c, TopStack(a));
            PopStack(a);
        }
        else if (EmptyStack(a)) {
            PushStack(c, TopStack(b));
            PopStack(b);
        }
        else if (EmptyStack(b)) {
            PushStack(c, TopStack(a));
            PopStack(a);
        }
        else{
            PushStack(c, TopStack(b));
            PopStack(b);
        }
    }
    DestroyStack(a);
    DestroyStack(b);
    ReverseStack(c);
}
stack * MergeSortStack(stack * s, int left, int right) {
    if (left + 1 == right) {
        return s;
    }
    int middle = (left + right) / 2;
    stack * l = malloc(sizeof(stack));
    stack * r = malloc(sizeof(stack));
    CreateStack(l);
    CreateStack(r);
    for (int i = left; i != middle; ++i) {
        PushStack(l, TopStack(s));
        PopStack(s);
    }
    for (int i = middle; i != right; ++i) {
        PushStack(r, TopStack(s));
        PopStack(s);
    }
    l = MergeSortStack(l, left, middle);
    r = MergeSortStack(r, middle, right);
    stack * t = malloc(sizeof(stack));
    CreateStack(t);
    MergeStack(t, l, r);
    free(l);
    free(r);
    return t;
}

