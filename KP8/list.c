#include "list.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
bool Equal(const iterator *left, const iterator * right) {
    return left->node == right->node;
}
iterator next(list * l, iterator * i) {
    if (i->node == NULL) {
        iterator j = {i->node->next};
        return j;
    }
    iterator j = {i->node->next};
    return j;
}
iterator prev(list * l, iterator * i) {
    iterator res;
    for (iterator j = first(l); j.node != i->node; j = next(l, &j)) {
        res = j;
    }
    return res;

}
char * fetch(const iterator * i) {
    return i->node->data;
}
void store(const iterator * i, char * t) {
    strcpy(i->node->data, t);
}
iterator first(list * l) {
    iterator i = {l->head};
    return i;
}
iterator end(list * l) {
    iterator i = {NULL};
    return i;
}

iterator last(list * l) {
    iterator res;
    for (iterator i = first(l); i.node != end(l).node; i = next(l, &i)) {
        res = i;
    }
    return res;
}
list * create() {
    list * l = (list *) malloc(sizeof(list));
    l->head = NULL;
    l->size = 0;
    return l;
}

int size(list * l) {
    return l->size;
}

bool empty(list * l) {
    return l->head == NULL;
}
iterator insert(list * l, iterator * i, char * t) {
    iterator new = {(struct item *)malloc(sizeof(struct item))};
    strcpy(new.node->data, t);
    l->size++;
    if (i->node == NULL) {
        l->head = new.node;
        l->head->next = NULL;
        return new;
    }
    new.node->next = i->node->next;
    i->node->next = new.node;
    return new;
}
iterator delete(list * l, iterator * i) {
    if (i->node == l->head) {
        struct item *tmp = l->head->next;
        free(i->node);
        l->head = tmp;
        iterator res = {l->head};
        l->size--;
        return res;
    }
    iterator p = prev(l, i);
    p.node->next = i->node->next;
    free(i->node);
    l->size--;
    return p;
}
void print(list *l) {
    int j = 0;
    printf("list: [");
    for(iterator i = first(l); i.node != end(l).node; i = next(l, &i), ++j) {
        printf("%s ", i.node->data);
    }
    printf("]\n");
}
iterator push_back(list * l, char * t) {
    iterator new = {(struct item *)malloc(sizeof(struct item))};
    strcpy(new.node->data, t);
    l->size++;
    if (l->head == NULL) {
        l->head = new.node;
        l->head->next = NULL;
        return new;
    }
    new.node->next = NULL;
    last(l).node->next = new.node;
    return new;
}
iterator find (list * l, char * t) {
    iterator res = {NULL};
    for(iterator i = first(l); i.node != end(l).node; i = next(l, &i)) {
        if (!strcmp(i.node->data, t)) {
            res = i;
            break;
        }
    }
    return res;
}
iterator at (list * l, int k)
{
    int j = 0;
    for(iterator i = first(l); i.node != end(l).node; i = next(l, &i), ++j) {
        if (j == k) {
            return i;
        }
    }
    iterator res = {NULL};
    return res;
}
iterator swap (list * l, int k) {
    iterator center = at(l, k);
    if (center.node == NULL || center.node == l->head || center.node == last(l).node) {
        iterator res = {NULL};
        return res;
    }
    iterator p = prev(l, &center);
    iterator n = next(l, &center);
    if (n.node == last(l).node && p.node == l->head){
        center.node->next = p.node;
        n.node->next = center.node;
        p.node->next = NULL;
        l->head = n.node;
        return center;
    }
    if (p.node == l->head) {
        struct item * tmpNext = n.node->next;
        center.node->next = p.node;
        n.node->next = center.node;
        p.node->next = tmpNext;
        l->head = n.node;
        return center;
    }
    if (n.node == last(l).node) {
        struct item * tmpPrev = prev(l, &p).node;
        center.node->next = p.node;
        n.node->next = center.node;
        tmpPrev->next = n.node;
        p.node->next = NULL;
        return center;
    }
    struct item * tmpPrev = prev(l, &p).node;
    struct item * tmpNext = n.node->next;
    center.node->next = p.node;
    n.node->next = center.node;
    tmpPrev->next = n.node;
    p.node->next = tmpNext;
    return center;
}
void destroy(list * l) {
    iterator start = first(l);
    while (!empty(l)) {
        start = delete(l, &start);
    }
    l->size = 0;
}
