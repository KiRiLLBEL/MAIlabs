#ifndef DEQUE_H
#define DEQUE_H
#include "stdlib.h"
#include "stdbool.h"
#include "stdio.h"
struct ItemDeque {
    int data;
    struct ItemDeque * prev;
    struct ItemDeque * next;
};
typedef struct {
    struct ItemDeque * front;
    struct ItemDeque * back;
    int size;
} deque;
void CreateDeque(deque * d);
bool EmptyDeque(deque * d);
int SizeDeque(deque * d);
bool PushBackDeque(deque * d, int t);
bool PushFrontDeque(deque * d, int t);
bool PopBackStack(deque * d);
bool PopFrontStack(deque * d);
int FrontDeque(deque * d);
int BackDeque(deque * d);
void DestroyDeque(deque * d);
#endif