#include <iostream>
#include "derivativeMethods.h"
using namespace  std;

double f_m(double x, double y1, double y2) {
    return  (2 * y1) / (x * x * (x + 1));
}

double exactSolution(double x) {
    return 1.0 / x + 1.0;
}

double rungeRombergError(const vector<double>& y_h, const vector<double>& y_h2, double r) {
    double error = 0.0;
    for (size_t i = 0; i < y_h.size(); ++i) {
        error = max(error, abs(y_h2[2 * i] - y_h[i]) / (pow(2, r) - 1));
    }
    return error;
}

void rungeRombergErrorShooting(const vector<vector<double>>& res_h, const vector<vector<double>>& res_h2) {
    const int width = 15;
    const int precision = 6;

    cout << "+---------------+---------------+---------------+" << endl;
    cout << "|       x       |    Error y    |    Error y'   |" << endl;
    cout << "+---------------+---------------+---------------+" << endl;
    for (int i = 0; i < res_h[0].size(); ++i) {
        double error_y1 = (res_h2[1][2 * i] - res_h[1][i]) / (pow(2, 4) - 1);
        double error_y2 = (res_h2[2][2 * i] - res_h[2][i]) / (pow(2, 4) - 1);
        cout << "| " << setw(width - 2) << setprecision(precision) << res_h[0][i] << " | "
             << setw(width - 2) << setprecision(precision) << error_y1 << " | "
             << setw(width - 2) << setprecision(precision) << error_y2 << " |" << endl;
    }
    cout << "+---------------+---------------+---------------+" << endl;
}

int main() {
    cout << "Real value:" << "\n";
    printTable(1, 2, 0.2, exactSolution);

    double a = 1, b = 2;
    double alpha = 2, beta = 1.5;
    double h = 0.2;
    double eps = 0.0001;

    cout << "\nShooting method:" << "\n";
    shootingMethod(f_m, a, b, alpha, beta, eps, h, 6);
    cout << "\nRunge-Romberg error estimate for Shooting Method:" << "\n";
    rungeRomberg(rungeKutta4, f_m, a, alpha, 0, h, 6);

    std::function<double(double)> p = [](double x) {
        return 0;
    };
    std::function<double(double)> q = [](double x) {
        return -2 / (x * x * (x + 1));
    };
    std::function<double(double)> f = [](double x) {
        return 0.0;
    };

    double y0 = 2.0;
    double y1 = 1.5;

    vector<double> x_h, y_h, x_h2, y_h2;

    cout << "\nFinite difference Method:" << "\n";
    finiteDifferenceMethod(a, b, y0, y1, h, p, q, f, x_h, y_h);

    cout << "\nFinite difference Method with h/2:" << "\n";
    finiteDifferenceMethod(a, b, y0, y1, h / 2, p, q, f, x_h2, y_h2);

    double error = rungeRombergError(y_h, y_h2, 2);

    cout << "\nError Finite Difference Method:" << endl;
    cout << "+---------------+---------------+" << endl;
    cout << "|       x       |     Error y   |" << endl;
    cout << "+---------------+---------------+" << endl;

    double maxError = 0.0;
    for (size_t i = 0; i < x_h.size(); ++i) {
        double exact = exactSolution(x_h[i]);
        double error = abs(y_h[i] - exact);
        maxError = max(maxError, error);
        cout << "| " << setw(13) << setprecision(6) << x_h[i] << " | "
             << setw(13) << setprecision(6) << error << " |" << endl;
    }
    cout << "+---------------+---------------+" << endl;

    return 0;
}
