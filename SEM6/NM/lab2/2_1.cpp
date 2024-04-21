#include "Solving_methods.h"
#include <iostream>
#include <valarray>
using namespace std;

double f(double x) {
    return sqrt(1 - x * x) - exp(x) + 0.1;
}

double f_d(double x) {
    return -exp(x) - x / (sqrt(1 - x * x));
}

double f_dd(double x) {
    return -exp(x) - 1 / (sqrt(1 - x * x) - (x * x) / pow(1 - x * x, 1.5));
}

double phi(double x, double lambda) {
    return x + lambda * (sqrt(1 - x * x) - exp(x) + 0.1);
}

double phi_x(double x, double lambda) {
    return lambda * (-exp(x) - x / (sqrt(1 - x * x))) + 1;
}

int main() {
    cout << "Iteration method:\n";
    cout << iterationMethod(phi, phi_x, 0, 1, 1, 0.1, 0.00001) << "\n";
    cout << "\n";
    cout << "Newton method:\n";
    cout << newtonMethod(f, f_d, f_dd, 0, 0.9, 0.00001) << "\n";
    return 0;
}