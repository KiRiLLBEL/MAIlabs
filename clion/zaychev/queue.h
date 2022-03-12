#ifndef QUEUE_H
#define QUEUE_H
#include "stdlib.h"
#include "stdbool.h"
struct Item {
    int data;
    struct Item * next;
};
typedef struct {
    struct Item* first;
    struct Item* last;
    int size;
} queue;
void Create (queue *q);
bool Empty (const queue *q);
int Size (const queue *q);
bool Push(queue *q, const int t);
bool Pop(queue *q);
int Top(const queue *q);
void Destroy(queue *q);
#endif QUEUE_H