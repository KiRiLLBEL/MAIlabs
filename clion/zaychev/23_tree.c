#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree1.h"

#define DEEP 0
#define max(x,y) ((x) > (y) ? (x) : (y))


struct _tree {
    TreeItem value;
    Tree child;
    Tree sibling;
}; 

Tree tree_create(TreeItem value)
{
    Tree tree = (Tree) malloc(sizeof(*tree));
    if(!tree) {
        fprintf(stderr, "%s\n", "Error: no memory");
        exit(1);
    }
    tree->value = value;
    tree->child = NULL;
    tree->sibling = NULL;
    return tree;
}

void tree_add_node(Tree tree, TreeItem parent, TreeItem value)
{
    Tree parent_node = tree_find(tree, parent);
    if(parent_node) {
        if(!parent_node->child) {
            parent_node->child = tree_create(value);
        } else {
            parent_node = parent_node->child;
            parent_node->sibling = tree_create(value);
        }
    } else {
        printf("Указанная родительская вершина не найдена.\n");
    }
}

Tree tree_find(Tree tree, TreeItem c)
{
    if(!tree) {
    	printf("Нет корня");
        return NULL;
    }

    if(tree->value == c) {
        return tree;
    }

    Tree result = NULL;
    if(tree->child) {
        result = tree_find(tree->child, c);
        if(result) return result;
    }

    if(tree->sibling) {
        result = tree_find(tree->sibling, c);
        if(result) return result;
    }

}


void tree_del_node(Tree tree, TreeItem value)//?????????
{
    if(tree->child) {
        if(tree->child->value == value) {
            Tree tmp = tree->child;
            tree->child = tree->child->sibling;
            if (tmp->child) {
                tree_destroy(tmp->child);
            }
            free(tmp);
            tmp = NULL;
            return;
        } else {
            tree_del_node(tree->child, value);
        }
    }


    if(tree->sibling) {
        if(tree->sibling->value == value) {
            Tree tmp = tree->sibling;
            tree->sibling = tree->sibling->sibling;
            if(tmp->child) {
                tree_destroy(tmp->child);
            }
            free(tmp);
            tmp = NULL;
            return;
        } else {
            tree_del_node(tree->sibling, value);
        }
    }
}

void tree_destroy(Tree tree)
{

    if(tree->child) {
        tree_destroy(tree->child);
    }
    if(tree->sibling) {
        tree_destroy(tree->sibling);
    }
    free(tree);
    tree = NULL;
}

void tree_print(Tree tree)
{
    tree_print_node(tree, 0);
}

void tree_print_node(Tree tree, int indent)
{
    for(int i = 0; i < indent; ++i) {
        printf("|");
        if(i==indent-1) printf(">");
    }
    
    printf("%d\n", tree->value);
    if(tree->child) {
        tree_print_node(tree->child, indent + 1);
    }
    if(tree->sibling) {
        tree_print_node(tree->sibling, indent);
    }
}

void l(Tree tree, int *count)
{
	if(tree->child != NULL) {*count+=1; l(tree->child, count);}
	if(tree->sibling != NULL) {*count+=1; l(tree->sibling, count);}
	
}
