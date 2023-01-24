#include <stdio.h>
#include <dlfcn.h>
#include <math.h>
#include <stdlib.h>
int main(int argc, char * argv[]) {
    void * handler1;
    void * handler2;
    float(*Derivative)(float, float);
    char *(*translation)(long);
    if (argc > 2) {
        if(atoi(argv[1]) == 0) {
            if(atoi(argv[2]) == 1) {
                handler1 = dlopen("/home/kirill/localProjects/OSlabs/lab5/build/src/include/libder2.so", RTLD_LAZY);
                if (!handler1) {
                    fprintf(stderr, "Open of dynamic library der2 with error: %s\n", dlerror());
                    exit(-1);
                }
                Derivative = dlsym(handler1, "Derivative");
                printf("Derivative is %f\n", (*Derivative)(atof(argv[3]), atof(argv[4])));
                dlclose(handler1);
            } else {
                handler2 = dlopen("./include/libtrans2.so", RTLD_LAZY);
                if (!handler2) {
                    fprintf(stderr, "Open of dynamic library trans2 with error: %s\n", dlerror());
                    exit(-2);
                }
                translation = dlsym(handler2, "translation");
                char * answer = (*translation)(atoi(argv[3]));
                printf("result is %s\n", answer);
                dlclose(handler2);
            }
        }
        else if(atoi(argv[1]) == 1) {
            handler1 = dlopen("./include/libder1.so", RTLD_LAZY);
            if (!handler1) {
                fprintf(stderr, "Open of dynamic library der1 with error: %s\n", dlerror());
                exit(-1);
            }
            Derivative = dlsym(handler1, "Derivative");
            printf("Derivative is %f\n", (*Derivative)(atof(argv[2]), atof(argv[3])));
            dlclose(handler1);
        }
        else if(atoi(argv[1]) == 2) {
            handler2 = dlopen("./include/libtrans1.so", RTLD_LAZY);
            if (!handler2) {
                fprintf(stderr, "Open of dynamic library trans1 with error: %s\n", dlerror());
                exit(-2);
            }
            translation = dlsym(handler2, "translation");
            char * answer = (*translation)(atoi(argv[2]));
            printf("result is %s\n", answer);
            dlclose(handler2);
        }
    }
}