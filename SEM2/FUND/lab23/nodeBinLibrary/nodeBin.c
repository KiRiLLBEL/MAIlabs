#include "nodeBin.h"
nodeBin * makeNodeBin(int key) {
    nodeBin *n = (nodeBin*)malloc(sizeof(nodeBin));
    n->key = key;
    n->left = NULL;
    n->right = NULL;
    return n;
}
void freeNodeBin(nodeBin * n) {
    printf("free node with key %d\n", n->key);
    if (n->left) // or "if (n->left != NULL)"
        freeNodeBin(n->left);
    if (n->right)
        freeNodeBin(n->right);
    free(n);
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
nodeBin * MinNodeBin(nodeBin *n) {
    if (n->left == NULL) {
        return n;
    }
    return MinNodeBin(n->left);
}
nodeBin * MaxNodeBin(nodeBin *n) {
    if (n->right == NULL) {
        return n;
    }
    return MaxNodeBin(n->right);
}
nodeBin * next(nodeBin *n, int key) {
    nodeBin * q = n;
    nodeBin * succresor = NULL;
    while (q != NULL) {
        if (q->key > key) {
            succresor = q;
            q = q->left;
        }
        else {
            q = q->right;
        }
    }
    return succresor;
}
nodeBin * prev(nodeBin *n, int key) {
    nodeBin * q = n;
    nodeBin * parent = NULL;
    while (q != NULL) {
        if (q->key < key) {
            parent = q;
            q = q->right;
        }
        else {
            q = q->left;
        }
    }
    return parent;
}
nodeBin * removeNodeBin(nodeBin *n, int key) {
    if (n->key > key) {
        n->left = removeNodeBin(n->left, key);
    }
    else if (n->key < key) {
        n->right = removeNodeBin(n->right, key);
    }
    else if (n->right != NULL && n->left != NULL) {
        n->key = MinNodeBin(n->right)->key;
        n->right = removeNodeBin(n->right, n->key);
    }
    else {
        if (n->right != NULL) {
            nodeBin *t = n->right;
            free(n);
            n = t;
        } else if (n->left != NULL) {
            nodeBin *t = n->left;
            free(n);
            n = t;
        } else {
            free(n);
            n = NULL;
        }
    }
    return n;
}
void leafBin(nodeBin *n, int * count) {
    if (n->left) {
        leafBin(n->left, count);
    }
    if (n->right) {
        leafBin(n->right, count);
    }
    if (n->left == NULL && n->right == NULL) {
        ++*count;
    }
}
int leafsBin(nodeBin *n) {
    int count = 0;
    leafBin(n, &count);
    return count;
}