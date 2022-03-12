#include "queue.h"
void Create (queue *q) {
    q->first = q->last = malloc(sizeof(struct Item));

}
bool Empty (const queue *q) {
    return q->first == q->last;
}
int size (const queue *q) {
    return q->size;
}
bool Push(queue *q, const int t) {
    if(!(q->last->next = malloc(sizeof(struct Item))))
        return false;
    q->last->data = t;
    q->last = q->last->next;
    q->size++;
    return true;
}
bool Pop(queue *q){
    if(q->first == q->last) {
        return false;
    }
    struct item *pi = q->first;
    q->first = q->first->next;
    q->size--;
    free(pi);
    return true;
}
int Top(const queue *q) {
    if (q->first != q->last)
        return q->first->data;
}
void Destroy(queue *q) {
    while(!Empty(q)) {
        struct item *pi = q->first;
        q->first = q->first->next;
        free(pi);
    }
    free(q->first);
    q->first = q->last = 0;
    q->size = 0;
}