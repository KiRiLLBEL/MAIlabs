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
    addNode(n, 10, 5);
    printNode(n);
    return 0;
}
