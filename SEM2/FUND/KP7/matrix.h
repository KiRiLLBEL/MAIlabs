#ifndef MATRIX_H
#define MATRIX_H
#define MAXHEIGHT 100
#define MAXWEIGHT 100
#define MAXSIZE 100
#include "stdbool.h"
typedef struct _Matrix {
    int height;
    int weight;
    int count;
    int CIP[MAXHEIGHT];
    int PI[MAXWEIGHT];
    double YE[MAXSIZE];
} Matrix;
Matrix * create_matrix(int height, int weight);
bool input_matrix(char * s, Matrix * m);
void print_matrix(Matrix *m);
void function_matrix(Matrix * m, double input);
void destroy_matrix(Matrix * m);
#endif