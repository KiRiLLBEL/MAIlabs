#include "vector.h"
void CreateVector(Vector *v, int _size) {
    v->size = _size;
    v->data = (int *)malloc(sizeof(int) * v->size);
}
bool EmptyVector(Vector * v) {
    return v->size == 0;
}
int SizeVector(Vector * v) {
    return v->size;
}
int LoadVector(Vector *v, int i) {
    if((i >= 0) && (i < v->size))
        return v->data[i];
}
void SaveVector(Vector *v, int i, int t) {
    if((i >= 0) && (i < v->size))
        v->data[i] = t;
}
void ResizeVector(Vector* v, int _size) {
    v->size = _size;
    v->data = (int *)realloc(v->data, sizeof(_size) * v->size);
}
bool EqualVector(Vector* l, Vector* r) {
    if(l->size != r->size)
        return false;
    for (int i = 0; i < l->size; ++i)
        if(l->data[i] != r->data[i])
            return false;
    return true;
}
void DestroyVector(Vector * v) {
    v->size = 0;
    free(v->data);
}