#ifndef _TREE_H_
#define _TREE_H_

#include <stdlib.h>
#include "lexer.h"

typedef struct tree_node *Tree;
struct tree_node {
    Token node;
    Tree left;
    Tree right;
};

Tree tree_create(Token tokens[], int idx_left, int idx_right);
void tree_print(Tree t, size_t depth);
void tree_infix(Tree t);
void tree_delete(Tree *t);
#endif

