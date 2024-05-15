#include <iostream>
#include <vector>
#define WITHOUT_NUMPY
#include "Polynoms.h"

using namespace std;
namespace plt = matplotlibcpp;

int main() {
    vector<double> X = {1, 1.5, 2.0, 2.5, 3.0};
    vector<double> Y = {0.0, 0.40547, 0.69315, 0.91629, 1.0986};
    cout << linearDerivative(X, Y, 2.0) << "\n";
    cout << derivativeUsingQuadraticInterpolation(X, Y, 2.0) << "\n";
    cout << secondDerivativeAtX(X, Y, 2.0) << "\n";

    return 0;
}