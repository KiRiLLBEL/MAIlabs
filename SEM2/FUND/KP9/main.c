#include <stdio.h>
#include "map.h"
#include "stdbool.h"
bool isInt(const char*str) {
    while(*str)  {
        if((*str< '0' || *str > '9') && *str != '-' && *str != '.')
            return false;
        *str++;
    }
    return true;
}
int main() {
    map * m = create_map();
    FILE * fin = fopen("input.txt", "r");
    read_table(m, fin);
    fclose(fin);
    bool programDo = true;
    while (programDo) {
        printf("1. Print\n2. Binary search\n3. Sort\n4. Reverse\n5. diffuse\n6. Exit\n");
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
            else {
                printf("Error, incorrect input\n");
            }
        }
        char number[10];
        int searchNumber;
        bool isNumber = true;
        switch (switcher) {
            case 1:
                print_table(m);
                printf("\n");
                break;
            case 2:
                while (isNumber) {
                    printf("Input key\n");
                    scanf("%s", number);
                    if (isInt(number)) {
                        isNumber = false;
                        searchNumber = strtol(number, NULL, 10);
                    } else {
                        printf("Error, incorrect input\n");
                    }
                }
                bin_search(m, searchNumber);
                break;
            case 3:
                sort(m);
                break;
            case 4:
                reverse_table(m);
                break;
            case 5:
                diffuse(m);
                break;
            case 6:
                programDo = false;
                break;
            default:
                printf("Error, incorrect input\n");
                break;
        }
    }
    delete_map(m);
    return 0;
}
