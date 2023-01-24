#ifndef QUEUE_H
#define QUEUE_H
#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
typedef struct{
    FILE * fqueue;
} Queue;
void FCreateQueue(Queue * q);
bool FEmptyQueue(Queue * q);
void FPushQueue(Queue * q, int t);
int FTopQueue(Queue * q);
void FPopQueue(Queue * q);
void FDestroyQueue(Queue * q);
#endif