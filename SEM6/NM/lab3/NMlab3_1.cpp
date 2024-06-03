#include <iostream>
#include <cmath>
#include <vector>
#define WITHOUT_NUMPY
#include "Polynoms.h"

using namespace std;


double f(double x) {
    return tan(x);
}

int main() {
    vector<double> X1 = {0, M_PI/8, 2*M_PI/8, 3*M_PI/8};
    vector<double> Y1 = {0, 0.4142, 1, 2.4142};
    vector<double> X2 = {0, M_PI/8, M_PI/3, 3*M_PI/8};
    vector<double> Y2 = {0, 0.4142, 1.7320, 2.4142};
    double x = 3 * M_PI / 16;
    cout << "Lagrange first: ";
    cout << lagrangePolynomial(X1, Y1, x);
    cout << "\nNewton first: ";
    cout << NewtonPolynomial(X1, Y1).evaluate(x);
    cout << "\nLagrange second: ";
    cout << lagrangePolynomial(X2, Y2, x);
    cout << "\nNewton second: ";
    cout << NewtonPolynomial(X2, Y2).evaluate(x);
    cout << "\nReal value: ";
    cout << f(x) << "\n";
    return 0;
}
