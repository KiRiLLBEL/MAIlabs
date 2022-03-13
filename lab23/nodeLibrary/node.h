#ifndef NODE_H
#define NODE_H
#include <stdio.h>
#include "stdlib.h"
typedef struct node {
    struct node ** sons;
    int key;
    int count;
} node;
node * makeNode(int x);
void freeNode(node * n);
void printParent (node *n, int deep);
void printSons (node *n, int deep);
void printNode (node *n);
node * findNode (node *n, int key);
void addNode(node * n, int parentKey, int x);
node *findParent (node *f, node *p);
void removeNode(node*n, node *f);
void Leaf(node *n, int * count);
int Leafs(node *n);
#endif