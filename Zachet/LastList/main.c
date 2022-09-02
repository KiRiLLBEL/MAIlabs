#include <stdio.h>
#include "stdlib.h"
typedef struct nodeBin {
    struct nodeBin* left;
    struct nodeBin* right;
    int key;
} nodeBin;
nodeBin * makeNodeBin(int key) {
    nodeBin *n = (nodeBin*)malloc(sizeof(nodeBin));
    n->key = key;
    n->left = NULL;
    n->right = NULL;
    return n;
}
nodeBin * findNodeBin(nodeBin *n, int key) {
    if (n == NULL || n->key == key) {
        return n;
    }
    if (key < n->key) {
        return findNodeBin(n->left, key);
    }
    else {
        return findNodeBin(n->right, key);
    }
}
void printParentBin (nodeBin *n, int deep) {
    if (deep != 0) {
        printf("=%d", n->key);
    }
    else {
        printf("%d", n->key);
    }
}
void printSonsBin (nodeBin *n, int deep) {
    for (int i = 0; i < deep - 1; ++i) {
        printf("| ");
    }
    if (deep != 0)
        printf("|");
    printParentBin(n, deep);
    printf("\n");
    int deepCopy = deep;
    if (n->left) {
        printSonsBin(n->left, ++deepCopy);
    }
    deepCopy = deep;
    if (n->right) {
        printSonsBin(n->right, ++deepCopy);
    }
}
void dfs(nodeBin * tree, int depth, int * depthMax, nodeBin ** leafMax) {
    if (tree != NULL) {
        if(depth > *depthMax) {
            *depthMax = depth;
            *leafMax = tree;
        }
        dfs(tree->left, depth + 1, depthMax, leafMax);
        dfs(tree->right, depth + 1, depthMax, leafMax);
    }
}
void addNodeBin(nodeBin *n, int key) {
    if (findNodeBin(n, key)) {
        printf("Error, element already created\n");
    }
    else {
        if (n->key > key) {
            if(n->left == NULL)
                n->left = makeNodeBin(key);
            else
                addNodeBin(n->left, key);
        }
        else {
            if(n->right == NULL)
                n->right = makeNodeBin(key);
            else
                addNodeBin(n->right, key);
        }
    }
}
int main () {
    nodeBin * nb;
    int depthMax = 0;
    nb = makeNodeBin(10);
    addNodeBin(nb, 1);
    addNodeBin(nb, 5);
    addNodeBin(nb, 20);
    addNodeBin(nb, 4);
    addNodeBin(nb, 21);
    addNodeBin(nb, 7);
    printSonsBin(nb, 0);
    nodeBin * leafMax = NULL; 
    dfs(nb, 1, &depthMax, &leafMax);
    printf("\n%d\n", leafMax->key);
}