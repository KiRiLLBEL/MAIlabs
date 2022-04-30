#include <stdio.h>
#include "matrix.h"
#include "stdlib.h"
#include "stdbool.h"
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
    Matrix * m;
    printf("Hello Victor\n");
    bool programDo = true;
    bool programStart = true;
    bool startBodyProgram = false;
    while (programDo) {
        if (startBodyProgram) {
            printf("1. Do function\n2. Print\n3. Exit\n");
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
                else {
                    printf("Error, incorrect input\n");
                }
            }
            switch (switcher) {
                case 1:
                    printf("Input number:\n");
                    char number[10];
                    int searchNumber;
                    bool isNumber = true;
                    while (isNumber) {
                        scanf("%s", number);
                        if (isInt(number)) {
                            isNumber = false;
                            searchNumber = strtol(number, NULL, 10);
                        }
                        else {
                            printf("Error, incorrect input\n");
                        }
                    }
                    function_matrix(m, searchNumber);
                    print_matrix(m);
                    break;
                case 2:
                    print_matrix(m);
                    break;
                case 3:
                    programDo = false;
                    break;
                default:
                    printf("Error, incorrect input\n");
                    break;
            }
        }
        if (programStart) {
            printf("1. Create matrix\n2. Exit\n");
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
                else {
                    printf("Error, incorrect input\n");
                }
            }
            switch (switcher) {
                case 1:
                    programStart = false;
                    bool numberIsInput = true;
                    int HEIGHT;
                    int WEIGHT;
                    printf("Input size of matrix:\n");
                    scanf("%d", &HEIGHT);
                    scanf("%d", &WEIGHT);
                    m = create_matrix(HEIGHT, WEIGHT);
                    printf("input address of input file:\n");
                    char s[128];
                    scanf("%s", s);
                    input_matrix(s, m);
                    print_matrix(m);
                    startBodyProgram = true;
                    break;
                case 2:
                    programDo = false;
                    break;
                default:
                    printf("Error, incorrect input\n");
                    break;
            }
        }
    }
    destroy_matrix(m);
    return 0;
}
