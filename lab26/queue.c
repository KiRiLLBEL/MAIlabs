#include "queue.h"
void CreateQueue(queue * q) {
    q->first = q->last = 0;
    q->size = 0;
}
bool EmptyQueue(queue * q) {
    return q->first == 0;
}
int SizeQueue(queue * q) {
    return q->size;
}
bool PushQueue(queue * q, int t) {
    struct ItemQueue * i  = malloc(sizeof(struct ItemQueue));
    if (!i)
        return false;
    i->data = t;
    if (q->last != 0) {
        q->last->next = i;
    }
    if (q->size == 0) {
        q->first = q->last = i;
    }
    else {
        q->last = i;
    }
    q->size++;
    return true;
}
bool PopQueue(queue * q) {
    if (q->first == q->last) {
        return false;
    }
    struct ItemQueue * t = q->first;
    q->first = q->first->next;
    q->size--;
    free(t);
    return true;
}
int TopQueue(queue * q) {
    if (q->first != q->last)
        return q->first->data;
}
void DestroyQueue(queue * q) {
    while (q->first != q->last) {
        struct ItemQueue * t = q->first;
        q->first = q->first->next;
        free(t);
    }
    q->first = q->last = 0;
    q->size = 0;
}