#include <stdio.h>
#include "list.h"
#include "stdlib.h"
#include "string.h"
bool isInt(const char*str) {
    while(*str)  {
        if((*str< '0' || *str > '9') && *str != '-' && *str != '.')
            return false;
        *str++;
    }
    return true;
}
int main() {
    list * l = create();
    printf("Hello Victor\n");
    bool programDo = true;
    bool startBodyProgram = true;
    while (programDo) {
        if (startBodyProgram) {
            printf("1. Add element\n2. Print\n3. delete element\n4. print size\n5. push back\n6. swap element\n7. Exit\n");
            char input[2];
            int switcher = 0;
            while (switcher == 0) {
                scanf("%s", input);
                if(!strcmp("1", input)){
                    switcher = 1;
                }
                else if(!strcmp("2", input)) {
                    switcher = 2;
                }
                else if(!strcmp("3", input)){
                    switcher = 3;
                }
                else if(!strcmp("4", input)){
                    switcher = 4;
                }
                else if(!strcmp("5", input)){
                    switcher = 5;
                }
                else if(!strcmp("6", input)){
                    switcher = 6;
                }
                else if(!strcmp("7", input)){
                    switcher = 7;
                }
                else {
                    printf("Error, incorrect input\n");
                }
            }
            char findString[MAXSIZE];
            iterator p;
            bool findItem = true;
            char number[10];
            int searchNumber;
            bool isNumber = true;
            switch (switcher) {
                case 1:
                    if (!empty(l)) {
                        print(l);
                        while (findItem) {
                            printf("Input parent string:\n");
                            scanf("%s", findString);
                            p = find(l, findString);
                            if (p.node == NULL) {
                                printf("Error, incorrect input\n");
                            } else {
                                findItem = false;
                            }
                        }
                        char inputString[MAXSIZE];
                        printf("Input string:\n");
                        scanf("%s", inputString);
                        insert(l, &p, inputString);
                    }
                    else {
                        printf("list haven't items\n");
                    }
                    break;
                case 2:
                    if (!empty(l)) {
                        print(l);
                    }
                    else {
                        printf("list haven't items\n");
                    }
                    break;
                case 3:
                    if (!empty(l)) {
                        while (findItem) {
                            printf("Input parent string:\n");
                            scanf("%s", findString);
                            p = find(l, findString);
                            if (p.node == NULL) {
                                printf("Error, incorrect input\n");
                            }
                            else {
                                findItem = false;
                            }
                        }
                        delete(l, &p);
                    }
                    else {
                        printf("list haven't items\n");
                    }
                    break;
                case 4:
                    printf("list size = %d\n", size(l));
                    break;
                case 5:
                    printf("Input string:\n");
                    char iString[MAXSIZE];
                    scanf("%s", iString);
                    push_back(l, iString);
                    break;
                case 6:
                    if (!empty(l) && size(l) >= 3) {
                        while (isNumber) {
                            printf("Input number:\n");
                            scanf("%s", number);
                            if (isInt(number)) {
                                isNumber = false;
                                searchNumber = strtol(number, NULL, 10);
                                if (searchNumber > size(l) || searchNumber < 0) {
                                    isNumber = true;
                                    printf("Error, incorrect input\n");
                                }
                            } else {
                                printf("Error, incorrect input\n");
                            }
                        }
                        if (swap(l, searchNumber).node != NULL) {
                            print(l);
                        } else {
                            printf("Error, list haven't items\n");
                        }
                    }
                    else {
                        printf("Error, list haven't items\n");
                    }
                    break;
                case 7:
                    programDo = false;
                    break;
                default:
                    printf("Error, incorrect input\n");
                    break;
            }
        }
    }
    destroy(l);
    return 0;
}