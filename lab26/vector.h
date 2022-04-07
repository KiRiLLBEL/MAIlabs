#ifndef VECTOR_H
#define VECTOR_H
#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
typedef struct {
    int * data;
    int size;
} Vector;
void CreateVector(Vector *v, int _size);
bool EmptyVector(Vector * v);
int SizeVector(Vector * v);
int LoadVector(Vector *v, int i);
void SaveVector(Vector *v, int i, int t);
void ResizeVector(Vector* v, int _size);
bool EqualVector(Vector* l, Vector* r);
void DestroyVector(Vector * v);
#endif