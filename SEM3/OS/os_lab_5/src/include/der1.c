#include <math.h>
float Derivative(float A, float deltaX) {
    return (cosf(A + deltaX) - cosf(A))/deltaX;
}