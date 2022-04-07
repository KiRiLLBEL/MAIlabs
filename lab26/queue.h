#ifndef QUEUE_H
#define QUEUE_H
#include "stdlib.h"
#include "stdbool.h"
#include "stdio.h"
struct ItemQueue {
    int data;
    struct ItemQueue * next;
};
typedef struct {
    struct ItemQueue * first;
    struct ItemQueue * last;
    int size;
} queue;
void CreateQueue(queue * q);
bool EmptyQueue(queue * q);
int SizeQueue(queue * q);
bool PushQueue(queue * q, int t);
bool PopQueue(queue * q);
int TopQueue(queue * q);
void DestroyQueue(queue * q);
#endif