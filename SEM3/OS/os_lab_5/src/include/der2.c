#include <math.h>
float Derivative(float A, float deltaX) {
    return (cos(A + deltaX) - cos(A - deltaX))/(2*deltaX);
}