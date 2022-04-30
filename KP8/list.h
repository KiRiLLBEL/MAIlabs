#ifndef LIST_H
#define LIST_H
#include "item.h"
#include "iterator.h"
typedef struct _list {
    struct item * head;
    int size;
} list;
bool Equal(const iterator *left, const iterator * right);
iterator next(list * l, iterator * i);
iterator prev(list * l, iterator * i);
char * fetch(const iterator * i);
void store(const iterator * i, char * t);
iterator first(list * l);
iterator end(list * l);
iterator last(list * l);
list * create();
int size(list * l);
bool empty(list * l);
iterator insert(list * l, iterator * i, char * t);
iterator delete(list * l, iterator * i);
iterator find(list * l, char * t);
void print(list *l);
iterator push_back(list * l, char * t);
iterator at (list * l, int k);
iterator swap (list * l, int k);
void destroy(list * l);
#endif