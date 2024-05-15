#ifndef LAB4_DERIVATIVEMETHODS_H
#define LAB4_DERIVATIVEMETHODS_H

#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include <iomanip>
#include "../lab1/Matrix.h"

using namespace std;
using namespace numeric;

vector<vector<double>>
eulerMethod(const std::function<double(double, double, double)> &f, double x0, double y1_0, double y2_0, double h,
            int n) {
    vector<double> x(n), y1(n), y2(n);
    x[0] = x0;
    y1[0] = y1_0;
    y2[0] = y2_0;

    for (int i = 1; i < n; ++i) {
        x[i] = x[i - 1] + h;
        y1[i] = y1[i - 1] + h * y2[i - 1];
        y2[i] = y2[i - 1] + h * f(x[i - 1], y1[i - 1], y2[i - 1]);
    }

    return vector<vector<double>>{x, y1, y2};

}


vector<vector<double>>
rungeKutta4(const std::function<double(double, double, double)> &f, double x0, double y1_0, double y2_0, double h,
            int n) {
    vector<double> x(n), y1(n), y2(n);
    x[0] = x0;
    y1[0] = y1_0;
    y2[0] = y2_0;

    for (int i = 1; i < n; ++i) {
        x[i] = x[i - 1] + h;

        double k1_y1 = h * y2[i - 1];
        double k1_y2 = h * f(x[i - 1], y1[i - 1], y2[i - 1]);

        double k2_y1 = h * (y2[i - 1] + 0.5 * k1_y2);
        double k2_y2 = h * f(x[i - 1] + 0.5 * h, y1[i - 1] + 0.5 * k1_y1, y2[i - 1] + 0.5 * k1_y2);

        double k3_y1 = h * (y2[i - 1] + 0.5 * k2_y2);
        double k3_y2 = h * f(x[i - 1] + 0.5 * h, y1[i - 1] + 0.5 * k2_y1, y2[i - 1] + 0.5 * k2_y2);

        double k4_y1 = h * (y2[i - 1] + k3_y2);
        double k4_y2 = h * f(x[i - 1] + h, y1[i - 1] + k3_y1, y2[i - 1] + k3_y2);

        y1[i] = y1[i - 1] + (k1_y1 + 2 * k2_y1 + 2 * k3_y1 + k4_y1) / 6;
        y2[i] = y2[i - 1] + (k1_y2 + 2 * k2_y2 + 2 * k3_y2 + k4_y2) / 6;
    }
    return vector<vector<double>>{x, y1, y2};
}

vector<vector<double>>
adams4(const std::function<double(double, double, double)> &f, double x0, double y1_0, double y2_0, double h, int n) {
    vector<double> x(n), y1(n), y2(n);
    x[0] = x0;
    y1[0] = y1_0;
    y2[0] = y2_0;

    for (int i = 1; i < 4; ++i) {
        x[i] = x[i - 1] + h;

        double k1_y1 = h * y2[i - 1];
        double k1_y2 = h * f(x[i - 1], y1[i - 1], y2[i - 1]);

        double k2_y1 = h * (y2[i - 1] + 0.5 * k1_y2);
        double k2_y2 = h * f(x[i - 1] + 0.5 * h, y1[i - 1] + 0.5 * k1_y1, y2[i - 1] + 0.5 * k1_y2);

        double k3_y1 = h * (y2[i - 1] + 0.5 * k2_y2);
        double k3_y2 = h * f(x[i - 1] + 0.5 * h, y1[i - 1] + 0.5 * k2_y1, y2[i - 1] + 0.5 * k2_y2);

        double k4_y1 = h * (y2[i - 1] + k3_y2);
        double k4_y2 = h * f(x[i - 1] + h, y1[i - 1] + k3_y1, y2[i - 1] + k3_y2);

        y1[i] = y1[i - 1] + (k1_y1 + 2 * k2_y1 + 2 * k3_y1 + k4_y1) / 6;
        y2[i] = y2[i - 1] + (k1_y2 + 2 * k2_y2 + 2 * k3_y2 + k4_y2) / 6;
    }

    for (int i = 4; i < n; ++i) {
        x[i] = x[i - 1] + h;

        y1[i] = y1[i - 1] + h / 24 * (55 * y2[i - 1] - 59 * y2[i - 2] + 37 * y2[i - 3] - 9 * y2[i - 4]);
        y2[i] = y2[i - 1] + h / 24 * (55 * f(x[i - 1], y1[i - 1], y2[i - 1]) - 59 * f(x[i - 2], y1[i - 2], y2[i - 2]) +
                                      37 * f(x[i - 3], y1[i - 3], y2[i - 3]) - 9 * f(x[i - 4], y1[i - 4], y2[i - 4]));
    }

    return vector<vector<double>>{x, y1, y2};
}

void rungeRomberg(
        const std::function<vector<vector<double>>(const std::function<double(double, double, double)> &, double,
                                                   double, double, double, int)> &method,
        const std::function<double(double, double, double)> &f, double x0, double y1_0, double y2_0, double h, int n) {
    vector<double> y1_h, y2_h, y1_h2, y2_h2;

    auto res1 = method(f, x0, y1_0, y2_0, h, n);
    auto res2 = method(f, x0, y1_0, y2_0, h / 2, 2 * n);
    y1_h = res1[1];
    y2_h = res1[2];
    y1_h2 = res2[1];
    y2_h2 = res2[2];

    const int width = 15;
    const int precision = 6;

    cout << "+---------------+---------------+---------------+" << endl;
    cout << "|       x       |    Error y    |    Error y'   |" << endl;
    cout << "+---------------+---------------+---------------+" << endl;
    for (int i = 0; i < n; ++i) {
        double x_i = x0 + i * h;
        double error_y1 = (y1_h2[2 * i] - y1_h[i]) / (pow(2, 4) - 1);
        double error_y2 = (y2_h2[2 * i] - y2_h[i]) / (pow(2, 4) - 1);
        cout << "| " << setw(width - 2) << setprecision(precision) << x_i << " | "
             << setw(width - 2) << setprecision(precision) << error_y1 << " | "
             << setw(width - 2) << setprecision(precision) << error_y2 << " |" << endl;

    }
    cout << "+---------------+---------------+---------------+" << endl;
}

void shootingMethod(const std::function<double(double, double, double)>& f, double a, double b, double alpha, double beta, double eps, double h, int n) {
    vector<vector<double>> result;
    vector<double> y_trial(n);
    vector<double> s_values;
    double s0 = 0;
    double s1 = 1.0;
    double y_b0, y_b1, s_new;

    auto result0 = rungeKutta4(f, a, alpha, s0, h, n);
    y_b0 = result0[1].back();
    auto result1 = rungeKutta4(f, a, alpha, s1, h, n);
    y_b1 = result1[1].back();

    cout << "+---------------+---------------+---------------+" << endl;
    cout << "|       s       |    f(b, y, s) |      |Ф(s)|   |" << endl;
    cout << "+---------------+---------------+---------------+" << endl;

    while (abs(y_b1 - beta) > eps) {
        s_new = s1 - (y_b1 - beta) * (s1 - s0) / (y_b1 - y_b0);
        s_values.push_back(s_new);
        cout << "| " << setw(13) << setprecision(6) << s1 << " | "
             << setw(13) << setprecision(6) << y_b1 << " | "
             << setw(13) << setprecision(6) << abs(y_b1 - beta) << " |" << endl;
        s0 = s1;
        y_b0 = y_b1;
        s1 = s_new;
        result = rungeKutta4(f, a, alpha, s1, h, n);
        y_b1 = result[1].back();
    }
    cout << "| " << setw(13) << setprecision(6) << s1 << " | "
         << setw(13) << setprecision(6) << y_b1 << " | "
         << setw(13) << setprecision(6) << abs(y_b1 - beta) << " |" << endl;
    cout << "+---------------+---------------+---------------+" << endl;

    cout << "+---------------+---------------+" << endl;
    cout << "|       x       |       y       |" << endl;
    cout << "+---------------+---------------+" << endl;

    for (int i = 0; i < n; ++i) {
        cout << "| " << setw(13) << setprecision(6) << result[0][i] << " | "
             << setw(13) << setprecision(6) << result[1][i] << " |" << endl;
    }
    cout << "+---------------+---------------+" << endl;
}

void finiteDifferenceMethod(double a, double b, double y0, double y1, double h,
                            const std::function<double(double)>& p,
                            const std::function<double(double)>& q,
                            const std::function<double(double)>& f,
                            vector<double>& x, vector<double>& y) {
    int n = static_cast<int>((b - a) / h) + 1;
    x.resize(n);
    y.resize(n);
    vector<double> rhs(n);

    for (int i = 0; i < n; ++i) {
        x[i] = a + i * h;
    }
    rhs[0] = h * h * f(x[0]) - (1 - p(x[0]) * h / 2) * y0;
    rhs[n - 1] = h * h * f(x[n - 1]) - (1 + p(x[n - 1]) * h / 2) * y1;
    for (int i = 1; i < n - 1; ++i) {
        rhs[i] = h * h * f(x[i]);
    }
    Matrix<double> A(n, n);
    for (int i = 0; i < n; ++i) {
        A[i][i] = -2 + h * h * q(x[i]);
        if (i > 0) A[i][i - 1] = 1 - p(x[i]) * h / 2;
        if (i < n - 1) A[i][i + 1] = (1 + p(x[i]) * h / 2);
    }

    y = tridiagonalSolve(A, rhs);

    cout << "+---------------+---------------+" << endl;
    cout << "|       x       |       y       |" << endl;
    cout << "+---------------+---------------+" << endl;
    cout << "| " << setw(13) << setprecision(6) << a << " | "
         << setw(13) << setprecision(6) << y0 << " |" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "| " << setw(13) << setprecision(6) << x[i] << " | "
             << setw(13) << setprecision(6) << y[i] << " |" << endl;
    }
    cout << "+---------------+---------------+" << endl;
}


void printTable(double a, double b, double h, std::function<double(double)> yFunc) {
    vector<double> x, y;
    for (double xi = a; xi <= b; xi += h) {
        x.push_back(xi);
        y.push_back(yFunc(xi));
    }

    cout << "+---------------+---------------+" << endl;
    cout << "|       x       |       y       |" << endl;
    cout << "+---------------+---------------+" << endl;

    for (size_t i = 0; i < x.size(); ++i) {
        cout << "| " << setw(13) << setprecision(6) << x[i] << " | "
             << setw(13) << setprecision(6) << y[i] << " |" << endl;
    }
    cout << "+---------------+---------------+" << endl;
}

void printResult(const vector<vector<double>> &res) {
    const int width = 15;
    const int precision = 6;

    cout << "+---------------+---------------+---------------+" << endl;
    cout << "|       x       |       y       |      y'       |" << endl;
    cout << "+---------------+---------------+---------------+" << endl;

    for (int i = 0; i < res[0].size(); ++i) {
        cout << "| " << setw(width - 2) << setprecision(precision) << res[0][i] << " | "
             << setw(width - 2) << setprecision(precision) << res[1][i] << " | "
             << setw(width - 2) << setprecision(precision) << res[2][i] << " |" << endl;
    }

    cout << "+---------------+---------------+---------------+" << endl;
}

#endif //LAB4_DERIVATIVEMETHODS_H
