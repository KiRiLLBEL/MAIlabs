#include "tree.h"
#include "transform.h"
#include <math.h>

int match_power(Tree *t)
{
    return ((*t) != NULL) && ((*t)->node.type == OPERATOR)
           && ((*t)->node.data.operator_name == '*')
           && ((((((*t)->left->node.type == INTEGER) && ((*t)->left->node.data.value_int < 0)) ||
               (((*t)->left->node.type == FLOATING)  && ((*t)->left->node.data.value_float < 0)))
           || ((((*t)->right->node.type == INTEGER) && ((*t)->right->node.data.value_int < 0)) || (((*t)->right->node.type == FLOATING)) && ((*t)->right->node.data.value_float < 0))) 
           || ((((*t)->right->node.type == OPERATOR) && ((*t)->right->node.data.operator_name == '-') 
           && ((((*t)->right->right->node.type == VARIABLE) && ((*t)->right->left == NULL)) || (((*t)->right->left->node.type == VARIABLE) && ((*t)->right->right == NULL)))) 
           || (((*t)->left->node.type == OPERATOR) 
           && ((*t)->left->node.data.operator_name == '-') 
           && ((((*t)->left->right->node.type == VARIABLE) && ((*t)->left->left == NULL)) 
           || (((*t)->left->left->node.type == VARIABLE) && ((*t)->left->right == NULL))))));
}

void transform_power(Tree *tl, Tree *tr)
{
    Tree tmpl = (Tree) malloc(sizeof(struct tree_node));
    Tree tmpr = (Tree) malloc(sizeof(struct tree_node));
    tmpl->node.type = (*tl)->node.type;
    tmpl->node.type = (*tr)->node.type;
    printf("Yes");
    if (tmpl->node.type == INTEGER && tmpr->node.type == INTEGER) {
        if (tmpl->node.data.value_int < 0 && tmpr->node.data.value_int < 0) {
            tmpl->node.data.value_int *= -1;
            tmpr->node.data.value_int *= -1;
        }
    }
    tree_delete(tl);
    tree_delete(tr);
    *tl = tmpl;
    *tr = tmpr;
}

void tree_transform(Tree *t)
{
    
    if ((*t) != NULL) {
        tree_transform(&((*t)->left));
        tree_transform(&((*t)->right));
        if (match_power(t)) {
            printf("OK");
            transform_power((*t)->left, (*t)->right);
        }
    }
}
