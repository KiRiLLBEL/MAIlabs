#include <stdio.h>
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"
#include "node.h"
#include "../nodeBinLibrary/nodeBin.h"
bool isInt(const char*str) {
    while(*str)  {
        if((*str< '0' || *str > '9') && *str != '-' && *str != '.')
            return false;
        *str++;
    }
    return true;
}
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
                int v = 0;
                char h[] = "";
                while (v == 0) {
                    printf("What you want to do?\n1: add new element\n2: print tree\n3: delete element\n4: print count of leafs\n5: exit\n");
                    scanf("%s", h);
                    if(!strcmp("1",h)){
                        v = 1;
                    }
                    else if(!strcmp("2",h)) {
                        v = 2;
                    }
                    else if(!strcmp("3",h)) {
                        v = 3;
                    }
                    else if(!strcmp("4",h)) {
                        v = 4;
                    }else if(!strcmp("5",h)) {
                        v = 5;
                    }else {
                        printf("Error, incorrect input\n");
                    }
                }
                switch (v) {
                    case 1:
                        printf("");
                        int t = 0;
                        char c[] = "";
                        bool rootTrue = true;
                        while (rootTrue) {
                            printf("addition of new element enter the key\n");
                            scanf("%s", c);
                            if (isInt(c)){
                                t = atoi(c);
                                rootTrue = false;
                            } else{
                                printf("Error, is not number\n");
                            }
                        }
                        addNodeBin(nb, t);
                        break;
                    case 2:
                        printSonsBin(nb, 0);
                        break;
                    case 3:
                        printf("");
                        int x = 0;
                        char h[] = "";
                        bool XisInt = true;
                        while (XisInt) {
                            printf("Enter the key\n");
                            scanf("%s", h);
                            if (isInt(h)){
                                x = atoi(h);
                                XisInt = false;
                            } else{
                                printf("Error, is not number\n");
                            }
                        }
                        if (findNodeBin(nb, x) == NULL) {
                            printf("Error, tree haven't this element\n");
                        }
                        else {
                            if (nb->key == x) {
                                if(nb->right == NULL && nb->left == NULL){
                                    freeNodeBin(nb);
                                    nb = NULL;
                                    TreeCreated = false;
                                }
                                else{
                                    nb = removeNodeBin(nb, x);
                                }
                            }
                            else {
                                nb = removeNodeBin(nb, x);
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
                        ProgramDo = false;
                        break;
                }
            }
            else {
                int v = 0;
                char h[] = "";
                while (v == 0) {
                    printf("What you want to do?\n1: add new element\n2: print tree\n3: delete element\n4: print count of leafs\n5: exit\n");
                    scanf("%s", h);
                    if(!strcmp("1",h)){
                        v = 1;
                    }
                    else if(!strcmp("2",h)) {
                        v = 2;
                    }
                    else if(!strcmp("3",h)) {
                        v = 3;
                    }
                    else if(!strcmp("4",h)) {
                        v = 4;
                    }else if(!strcmp("5",h)) {
                        v = 5;
                    }else {
                        printf("Error, incorrect input\n");
                    }
                }
                switch (v) {
                    case 1:
                        printf("");
                        bool PisInt = true;
                        bool TisInt = true;
                        char P[] = "";
                        int p = 0;
                        char T[] = "";
                        int t = 0;
                        while (PisInt && TisInt) {
                            printf("addition of new element enter parent and key\n");
                            scanf("%s", P);
                            if (isInt(P)){
                                p = atoi(P);
                                PisInt = false;
                            } else {
                                printf("Error, is not number\n");
                                PisInt = true;
                                continue;
                            }
                            scanf("%s", T);
                            if (isInt(T)){
                                t = atoi(T);
                                TisInt = false;
                            } else {
                                printf("Error, is not number\n");
                                TisInt = true;
                                continue;
                            }
                        }
                        addNode(n, p, t);
                        break;
                    case 2:
                        printNode(n);
                        break;
                    case 3:
                        printf("");
                        int x = 0;
                        char h[] = "";
                        bool XisInt = true;
                        while (XisInt) {
                            printf("Enter the key\n");
                            scanf("%s", h);
                            if (isInt(h)){
                                x = atoi(h);
                                XisInt = false;
                            } else{
                                printf("Error, is not number\n");
                            }
                        }
                        if (findNode(n, x) == NULL) {
                            printf("Error, tree haven't this element\n");
                        }
                        else{
                            if (n->key == x) {
                                freeNode(n);
                                n = NULL;
                                TreeCreated = false;
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
                        ProgramDo = false;
                        break;
                }
            }
        }
        else {
            char a[] = "";
            int x = 0;
            while (x == 0) {
                printf("What you want to do?\n1: Create new tree\n2: Exit\n");
                scanf("%s", a);
                if(!strcmp("1",a)){
                    x = 1;
                }
                else if(!strcmp("2",a)) {
                    x = 2;
                } else {
                    printf("Error, incorrect input\n");
                }
            }
            switch (x) {
                case 1:
                    printf("");
                    int z = 0;
                    char b[] = "";
                    while (z == 0) {
                        printf("What kind of tree you want to create\n1: Bin. tree\n2: Normal tree\n");
                        scanf("%s", b);
                        if(!strcmp("1",b)){
                            z = 1;
                        }
                        else if(!strcmp("2",b)) {
                            z = 2;
                        } else {
                            printf("Error, incorrect input\n");
                        }
                    }
                    switch (z) {
                        case 1:
                            printf("");
                            int root;
                            char c[] = "";
                            bool rootTrue = true;
                            while (rootTrue) {
                                printf("Creation of new tree, enter root\n");
                                scanf("%s", c);
                                if (isInt(c)){
                                    root = atoi(c);
                                    rootTrue = false;
                                } else{
                                    printf("Error, is not number\n");
                                }
                            }
                            nb = makeNodeBin(root);
                            printf("created new tree\n");
                            TreeCreated = true;
                            BinTreeCreated = true;
                            break;
                        case 2:
                            printf("");
                            char d[] = "";
                            int root2;
                            bool root2True = true;
                            while (root2True) {
                                printf("Creation of new tree, enter root\n");
                                scanf("%s", d);
                                if (isInt(d)){
                                    root2 = atoi(d);
                                    root2True = false;
                                } else{
                                    printf("Error, is not number\n");
                                }
                            }
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
                    ProgramDo = false;
                    break;
            }
        }
    }
    if (TreeCreated)
        if (BinTreeCreated)
            freeNodeBin(nb);
        else
            freeNode(n);
    return 0;
}
