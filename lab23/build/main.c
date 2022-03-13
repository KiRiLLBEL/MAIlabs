#include <stdio.h>
#include "stdlib.h"
#include "stdbool.h"
#include "node.h"

int main() {
    node * n = makeNode(10);
    addNode(n, 10, 9);
    addNode(n, 10, 8);
    addNode(n, 10, 7);
    addNode(n, 10, 6);
    addNode(n, 9, 5);
    addNode(n, 9, 4);
    addNode(n, 9, 3);
    addNode(n, 9, 2);
    addNode(n, 9, 1);
    printNode(n);
    printSonNode(n, 9);
    removeNode(n, findNode(n, 9));
    printNode(n);
    freeNode(n);
    return 0;
}
