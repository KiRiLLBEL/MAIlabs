#include "matrix.h"
#include "stdlib.h"
#include "stdio.h"
#include "math.h"
Matrix * create_matrix(int height, int weight) {
    Matrix * m = (Matrix *)malloc(sizeof(Matrix));
    m->height = height;
    m->weight = weight;
    return m;
}
bool input_matrix(char * s, Matrix * m) {
    FILE * input;
    input = fopen(s, "r");
    if (input == NULL) {
        fprintf(stderr, "Error, file not open");
        return false;
    }
    int count = 0;
    double number;
    for (int i = 0; i != m->height; ++i) {
        m->CIP[i] = count;
        for (int j = 0; j != m->weight; ++j) {
            if(fscanf(input, "%lf", &number)) {
                if(number != 0) {
                    m->PI[count] = j + 1;
                    m->YE[count] = number;
                    ++count;
                }
            }
        }
        m->YE[count] = 0;
        ++count;
    }
    m->count = count;
    fclose(input);
}
void print_matrix(Matrix *m) {
    int count = 0;
    for (int i = 0; i != m->height; ++i) {
        for (int j = 0; j != m->weight; ++j) {
            if(m->PI[count] == j + 1 && m->PI[count] != 0) {
                printf("%7.2lf ", m->YE[count]);
                ++count;

            }
            else {
                printf("%7d ", 0);
            }
        }
        ++count;
        printf("\n");
    }
}
void function_matrix(Matrix * m, double input) {
    double minElem = 0;
    double min = fabs(1e9 - input);
    for (int i = 0; i != m->count; ++i) {
        if(m->PI[i] != 0) {
            if (fabs(m->YE[i] - input) < min) {
                min = fabs(m->YE[i] - input);
                minElem = m->YE[i];
            }
        }
    }
    for (int i = 0; i != m->count; ++i) {
        if (m->YE[i] == minElem) {
            for (int j = 0; j != m->count; ++j) {
                if(m->PI[i] == m->PI[j]) {
                    if(m->YE[j] != minElem) {
                        m->YE[j] /= minElem;
                    }
                }
            }
            int line = 0;
            for (int j = 0; j != m->height; ++j) {
                if (i >= m->CIP[j])
                    line = j;
            }
            for (int j = m->CIP[line]; j != m->CIP[line] + m->weight; ++j) {
                if (m->PI[j] != 0) {
                    if (m->YE[j] != minElem)
                        m->YE[j] /= minElem;
                }
                else {
                    break;
                }
            }
        }
    }
}
void destroy_matrix(Matrix * m) {
    free(m);
    m = NULL;
}