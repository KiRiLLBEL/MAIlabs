#include "vector.h"

void Create (vector *v, int size) {
    v->size = size;
    v->data = malloc(sizeof(int) * v->size);
}
bool Empty (vector *v) {
    return v->size == 0;
}
int Size (vector *v) {
    return v->size;
}
int Load (vector *v, int i) {
    if (i >= 0 && i < v->size)
        return v->data[i];
}
void Save(vector *v, int i, int t) {
    if(i >= 0 && i < v->size) {
        v->data[i] = t;
    }
}
void Resize(vector *v, int newSize) {
    v->size = newSize;
    v->data = realloc(v->data, sizeof(int) * v->size);
}
bool Equal(vector *v, vector *u) {
    if (v->size != u->size)
        return false;
    for (int i = 0; i < v->size; ++i)
        if (v->data[i] != u->data[i])
            return false;
    return true;
}
void Destroy(vector *v) {
    v->size = 0;
    free(v->data);
}