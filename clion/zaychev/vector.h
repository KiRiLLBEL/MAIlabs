#ifndef VECTOR_H
#define VECTOR_H
#include "stdlib.h"
#include "stdbool.h"
typedef struct {
    int* data;
    int size;

} vector;
void Create (vector *v, int size);
bool Empty (vector *v);
int Size (vector *v);
int Load (vector *v, int i);
void Save(vector *v, int i, int t);
void Resize(vector *v, int newSize);
bool Equal(vector *v, vector *u);
void Destroy(vector *v);
#endif