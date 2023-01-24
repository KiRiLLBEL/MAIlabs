#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "prog1.h"
int main(int argc, char * argv[]) {
    int func = 0;
    long x = 0;
    float A = 0;
    float deltaX = 0;
    if(argc > 2) {
        func = atoi(argv[1]);
        if(func == 1) {
            A = atof(argv[2]);
            deltaX = atof(argv[3]);
            printf("Derivative at a point %f with delta %f is %f\n", A, deltaX, Derivative(A, deltaX));
        }
        if(func == 2) {
            x = atoi(argv[2]);
            printf("%s\n", translation(x));
        }
    }
}