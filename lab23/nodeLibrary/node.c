#include "node.h"
node * makeNode(int x) {
    node *n = malloc(sizeof(node));
    n->key = x;
    n->count = 0;
    n->sons = NULL;
    return n;
}

void freeNode(node * n) {
    for (int i = 0; i < n->count; ++i) {
        if (n->sons[i] != NULL) {
            freeNode(n->sons[i]);
        }
    }
    free(n->sons);
    n->sons = NULL;
    printf("free node with key %d\n", n->key);
    free(n);
    n = NULL;
}
void printParent (node *n, int deep) {
    if (deep != 0) {
        printf("-%d", n->key);
    }
    else {
        printf("%d", n->key);
    }
}
void printSons (node *n, int deep) {
    for (int i = 0; i < deep - 1; ++i) {
        printf("| ");
    }
    if (deep != 0)
        printf("|");
    printParent(n, deep);
    printf("\n");
    for (int i = 0; i < n->count; ++i) {
        int deepCopy = deep;
        printSons(n->sons[i], ++deepCopy);
    }
}
void printNode (node *n) {
    printSons(n, 0);
}
node * findNode (node *n, int key) {
    if (n->key == key)
        return n;
    if (n->count > 0) {
        for (int i = 0; i < n->count; ++i) {
            node * f = findNode(n->sons[i], key);
            if (f != NULL) {
                return f;
            }
        }
        return NULL;
    }
    else {
        return NULL;
    }
}
void addNode(node * n, int parentKey, int x) {
    node *f = findNode(n, parentKey);
    if (f != NULL) {
        if (f->count > 0) {
            f->sons = (node **)realloc(f->sons, sizeof(node *) * (f->count + 1));
            f->sons[f->count] = makeNode(x);
            f->count++;
        }
        else if (f->count == 0) {
            f->sons = (node **)malloc(sizeof(node *));
            f->sons[0] = makeNode(x);
            f->count = 1;
        }
    }
    else {
        printf("Error, parent not founded");
    }
}
node *findParent (node *f, node *p) {
    if (f->count>0) {
        for (int i = 0; i < f->count; ++i) {
            if (f->sons[i]->key == p->key)
                return f;
            else {
                node * s = findParent(f->sons[i], p);
                if (s != NULL)
                    return s;
            }
        }
        return NULL;
    }
    else
        return NULL;
}
void removeNode(node*n, node *f) {
    node * p = findParent(n, f);
    int del = 0;
    for (int i = 0; i < p->count; ++i)
        if (p->sons[i]->key == f->key) {
            del = i;
            break;
        }
    freeNode(f);
    for (int i = del; i < p->count-1; ++i)
        p->sons[i] = p->sons[i + 1];
    p->count--;
}
void Leaf(node *n, int * count) {
    for (int i = 0; i < n->count; ++i) {
        if (n->sons[i] != NULL) {
            Leaf(n->sons[i], count);
        }
    }
    if (n->count == 0) {
        ++*count;
    }
}
int Leafs(node *n) {
    int count = 0;
    Leaf(n, &count);
    return count;
}
void printSonNode (node* n, int key) {
    printNode(findNode(n, key));
}