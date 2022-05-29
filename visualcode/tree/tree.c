#include <tree.h>
#include <stdlib.h>
node * create (int root) {
    node * tree = (node *)malloc(sizeof(node));
    tree->key = root;
    tree->left = NULL;
    tree->right = NULL;
    return tree;
}
node * build (node * left, int root, node * right) {
     node * tree = (node *)malloc(sizeof(node));
    tree->key = root;
    tree->left = left;
    tree->right = right;
    return tree;
}
bool empty(node * tree) {
    if (tree->left == NULL && tree->right == NULL) 
        return false;
    return true;
}
int root(node * tree) {
    return tree->key;
}
node * right(node * tree) {
    return tree->right;
}
node * left(node * tree) {
    return tree->left;
}
void destroy(node * tree) {
    free(tree);
}