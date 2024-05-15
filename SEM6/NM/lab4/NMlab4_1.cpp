#include <iostream>
#include "derivativeMethods.h"
using namespace  std;

double f(double x, double y1, double y2) {
    return 2 * cos(x) - y1;
}

double fExact(double x) {
    return x * sin(x) + cos(x);
}

void compareWithExact(const vector<vector<double>>& result, double (*exactFunc)(double)) {
    const int width = 15;
    const int precision = 6;

    cout << "+---------------+---------------+---------------+---------------+" << endl;
    cout << "|       x       |       y       |    Exact y    |     Error     |" << endl;
    cout << "+---------------+---------------+---------------+---------------+" << endl;

    for (size_t i = 0; i < result[0].size(); ++i) {
        double exact_y = exactFunc(result[0][i]);
        double error = abs(result[1][i] - exact_y);
        cout << "| " << setw(width - 2) << setprecision(precision) << result[0][i] << " | "
             << setw(width - 2) << setprecision(precision) << result[1][i] << " | "
             << setw(width - 2) << setprecision(precision) << exact_y << " | "
             << setw(width - 2) << setprecision(precision) << error << " |" << endl;
    }
    cout << "+---------------+---------------+---------------+---------------+" << endl;
}

int main() {
    double x0 = 0, y1_0 = 1, y2_0 = 0, h = 0.1;
    int n = 11;

    cout << "Euler method:" << "\n";
    auto eulerRes = eulerMethod(f, x0, y1_0, y2_0, h, n);
    compareWithExact(eulerRes, fExact);

    cout << "\nRunge-Kutta method:" << "\n";
    auto rungeKuttaRes = rungeKutta4(f, x0, y1_0, y2_0, h, n);
    compareWithExact(rungeKuttaRes, fExact);

    cout << "\nAdams method:" << "\n";
    auto adamsRes = adams4(f, x0, y1_0, y2_0, h, n);
    compareWithExact(adamsRes, fExact);

    cout << "\nEuler method error by Runge Romberg:" << "\n";
    rungeRomberg(eulerMethod, f, x0, y1_0, y2_0, h, n);

    cout << "\nRunge-Kutta method error by Runge Romberg:" << "\n";
    rungeRomberg(rungeKutta4, f, x0, y1_0, y2_0, h, n);

    cout << "\nAdams method error by Runge Romberg:" << "\n";
    rungeRomberg(adams4, f, x0, y1_0, y2_0, h, n);

    return 0;
}