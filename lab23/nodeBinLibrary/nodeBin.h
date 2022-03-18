#ifndef NODEBIN_H
#define NODEBIN_H
#include <stdio.h>
#include "stdlib.h"
typedef struct nodeBin {
    struct nodeBin* left;
    struct nodeBin* right;
    int key;
} nodeBin;
nodeBin * makeNodeBin(int key);
void freeNodeBin(nodeBin * n);
void printParentBin (nodeBin *n, int deep);
void printSonsBin (nodeBin *n, int deep);
nodeBin * findNodeBin(nodeBin *n, int key);
void addNodeBin(nodeBin *n, int key);
nodeBin * MinNodeBin(nodeBin *n);
nodeBin * MaxNodeBin(nodeBin *n);
nodeBin * next(nodeBin *n, int key);
nodeBin * prev(nodeBin *n, int key);
nodeBin * removeNodeBin(nodeBin *n, int key);
void leafBin(nodeBin *n, int * count);
int leafsBin(nodeBin *n);
#endif