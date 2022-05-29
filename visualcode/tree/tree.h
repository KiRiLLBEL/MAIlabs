#ifndef TREE_H
#define TREE_H
#include <stdbool.h>
typedef struct node
{
    struct node * left;
    struct node * right;
    int key;
} node;
node * create (int root);
node * build (node * left, int root, node * right);
bool empty(node * tree);
int root(node * tree);
node * right(node * tree);
node * left(node * tree);
void destroy(node * tree);
#endif
