#include <iostream>
#include <cmath>
#include <vector>
#define WITHOUT_NUMPY
#include "Polynoms.h"

using namespace std;

int main() {
    CubicSpline spline({0.0, 0.9, 1.8, 2.7, 3.6}, {0.0, 0.36892, 0.85408, 1.7856, 6.3138});
    cout << "\nSpline: ";
    cout << spline.evaluate(1.5);
    plotCubicSpline(spline, {0.0, 0.9, 1.8, 2.7, 3.6}, {0.0, 0.36892, 0.85408, 1.7856, 6.3138});
}

