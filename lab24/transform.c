#include "tree.h"
#include "transform.h"
#include <math.h>

int match_power(Tree *t)
{
     return ((*t) != NULL) && ((*t)->node.type == OPERATOR)
           && ((*t)->node.data.operator_name == '^')
           && (((*t)->left->node.type == INTEGER) ||
               ((*t)->left->node.type == FLOATING))
           && ((*t)->right->node.type == INTEGER);
}

void transform_power(Tree *t)
{
    Tree tmp = (Tree) malloc(sizeof(struct tree_node));
    tmp->node.type = (*t)->left->node.type;

    float right = (*t)->right->node.data.value_int;

    if (tmp->node.type == INTEGER)
        tmp->node.data.value_int = pow((*t)->left->node.data.value_int, right);
    else // if (tmp->node.type == FLOATING)
        tmp->node.data.value_float = pow((*t)->left->node.data.value_float, right);

    tmp->left  = NULL;
    tmp->right = NULL;

    tree_delete(t);
    *t = tmp;
}

void tree_transform(Tree *t)
{
    if ((*t) != NULL) {
        tree_transform(&((*t)->left));
        tree_transform(&((*t)->right));

        if (match_power(t)) {
            transform_power(t);
        }
    }
}
