#include <stdio.h>
#include "stdlib.h"
#include "stdbool.h"
#include "node.h"
#include "../nodeBinLibrary/nodeBin.h"

int main() {
    node *n;
    nodeBin *nb;
    bool ProgramDo = true;
    bool TreeCreated = false;
    bool BinTreeCreated = false;
    printf("Program start\n");
    while (ProgramDo) {
        if (TreeCreated) {
            if (BinTreeCreated) {
                printf("What you want to do?\n1: add new element\n2: print tree\n3: delete element\n4: print count of leafs\n5: exit\n");
                int v = 0;
                scanf("%d", &v);
                switch (v) {
                    case 1:
                        printf("addition of new element enter the key\n");
                        int t = 0;
                        scanf("%d", &t);
                        addNodeBin(nb, t);
                        break;
                    case 2:
                        printSonsBin(nb, 0);
                        break;
                    case 3:
                        printf("Enter key\n");
                        int x = 0;
                        scanf("%d", &x);
                        if (findNodeBin(nb, x) == NULL) {
                            printf("Error, tree haven't this element\n");
                        }
                        else {
                            if (nb->key == x) {
                                printf("Error, removing root");
                            }
                            else {
                                removeNodeBin(nb, x);
                            }
                        }
                        break;
                    case 4:
                        printf("%d\n", leafsBin(nb));
                        break;
                    case 5:
                        printf("End of program\n");
                        ProgramDo = false;
                        break;
                    default:
                        printf("Error, incorrect input\n");
                        break;
                }
            }
            else {
                printf("What you want to do?\n1: add new element\n2: print tree\n3: delete element\n4: print count of leafs\n5: exit\n");
                int x = 0;
                scanf("%d", &x);
                switch (x) {
                    case 1:
                        printf("addition of new element enter parent and key\n");
                        int p = 0;
                        int t = 0;
                        scanf("%d %d", &p, &t);
                        addNode(n, p, t);
                        break;
                    case 2:
                        printNode(n);
                        break;
                    case 3:
                        printf("Enter key\n");
                        int x = 0;
                        scanf("%d", &x);
                        if (findNode(n, x) == NULL) {
                            printf("Error, tree haven't this element\n");
                        }
                        else{
                            if (n->key == x) {
                                printf("Error, removing root\n");
                            }
                            else {
                                removeNode(n, findNode(n, x));
                            }
                        }
                        break;
                    case 4:
                        printf("%d", Leafs(n));
                        break;
                    case 5:
                        printf("End of program\n");
                        ProgramDo = false;
                        break;
                    default:
                        printf("Error, incorrect input\n");
                        break;
                }
            }
        }
        else {
            printf("What you want to do?\n1: Create new tree\n2: Exit\n");
            int x = 0;
            scanf("%d", &x);
            switch (x) {
                case 1:
                    printf("What kind of tree you want to create\n1: Bin. tree\n2: Normal tree\n");
                    int z = 0;
                    scanf("%d", &z);
                    switch (z) {
                        case 1:
                            BinTreeCreated = true;
                            printf("Creation of new tree, enter root\n");
                            int root;
                            scanf("%d", &root);
                            nb = makeNodeBin(root);
                            printf("created new tree\n");
                            TreeCreated = true;
                            break;
                        case 2:
                            printf("Creation of new tree, enter root\n");
                            int root2;
                            scanf("%d", &root2);
                            n = makeNode(root2);
                            printf("created new tree\n");
                            TreeCreated = true;
                            break;
                        default:
                            printf("Error, incorrect input\n");
                            break;
                    }
                    break;
                case 2:
                    printf("End of program\n");
                    ProgramDo = false;
                    break;
                default:
                    printf("Error, incorrect input\n");
                    break;
            }
        }
    }
    if (TreeCreated)
        if (BinTreeCreated)
            freeNodeBin(n);
        else
            freeNode(n);
    return 0;
}
