#include "deque.h"
void CreateDeque(deque * d) {
    d->back = d->front = 0;
    d->size = 0;
}
bool EmptyDeque(deque * d) {
    return d->front == 0;
}
int SizeDeque(deque * d) {
    return d->size;
}
bool PushBackDeque(deque * d, int t) {
    struct ItemDeque * i = malloc(sizeof(struct ItemDeque));
    if (!i)
        return false;
    i->data = t;
    i->prev = d->back;
    i->next = 0;
    if (d->back != 0) {
        d->back->next = i;
    }
    if (d->size == 0) {
        d->front = d->back = i;
    }
    else {
        d->back = i;
    }
    d->size++;
    return true;
}
bool PushFrontDeque(deque * d, int t) {
    struct ItemDeque * i = malloc(sizeof(struct ItemDeque));
    if (!i)
        return false;
    i->data = t;
    i->next = d->front;
    i->prev = 0;
    if (d->front != 0) {
        d->front->prev = i;
    }
    if (d->size == 0) {
        d->front = d->back = i;
    }
    else {
        d->front = i;
    }
    d->size++;
    return true;
}
bool PopBackStack(deque * d) {
    if(!d->size)
        return  false;
    struct ItemDeque * i = d->back;
    d->back = d->back->prev;
    d->back->next = 0;
    d->size--;
    free(i);
    return true;
}
bool PopFrontStack(deque * d) {
    if(!d->size)
        return  false;
    struct ItemDeque * i = d->front;
    d->front = d->front->next;
    d->front->prev = 0;
    d->size--;
    free(i);
    return true;
}
int FrontDeque(deque * d) {
    if(d->front)
        return d->front->data;
}
int BackDeque(deque * d) {
    if(d->back)
        return d->back->data;
}
void DestroyDeque(deque * d) {
    while (d->front != d->back) {
        struct ItemDeque * i = d->front;
        d->front = d->front->next;
        d->front->prev = 0;
        free(i);
    }
    d->front = d->back = 0;
    d->size = 0;
}