#ifndef LIST_H
#define LIST_H
#include "stdlib.h"
#include "stdbool.h"

struct Item {
    struct Item* prev;
    struct Item* next;
    int data;
};
typedef struct {
    struct Item* node;
} Iterator;
typedef struct {
    struct Item * head;
    int size;
} List;
void Create(List *l) {
    l->head = malloc(sizeof(struct Item));
    l->head->next = l->head->prev = l->head;
    l->size = 0;
}
Iterator First(const List *l) {
    Iterator res = {l->head->next};
    return res;
}
Iterator Last(const List *l) {
    Iterator res = {l->head};
    return res;
}

bool Equal(const Iterator *lhs, const Iterator *rhs) {
    return lhs->node == rhs->node;
}
bool NotEqual(const Iterator *lhs, const Iterator *rhs) {
    return !Equal(lhs, rhs);
}
Iterator next(Iterator *i) {
    i->node = i->node->next;
    return *i;
}
Iterator prev(Iterator *i) {
    i->node = i->node->prev;
    return *i;
}
int Fetch(const Iterator* i) {
    return i->node->data;
}
void Store(const Iterator *i, const int t) {
    i->node->data = t;
}
bool Empty (const List *l) {
    Iterator fst = First(l);
    Iterator lst = Last(l);
    return Equal(&fst, &lst);
}
int Size(const List *l) {
    return l->size;
}
Iterator Insert (List *l, Iterator *i, const int t) {
    Iterator res = {malloc(sizeof(struct Item))};
    if(!res.node)
        return Last(l);
    res.node->data = t;
    res.node->next = i->node;
    res.node->prev = i->node->prev;
    res.node->prev->next = res.node;
    i->node->prev = res.node;
    l->size++;
    return res;
}
#endif