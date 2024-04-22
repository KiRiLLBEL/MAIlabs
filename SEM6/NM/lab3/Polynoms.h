#ifndef POLYNOMS_H
#define POLYNOMS_H

#include <vector>
#include <algorithm>
#include "../lab1/Matrix.h"
double lagrangePolynomial(const std::vector<double>& X, const std::vector<double>& Y, double x) {
    size_t n = X.size();
    double result = 0.0;

    for (int i = 0; i < n; i++) {
        double term = Y[i];
        for (int j = 0; j < n; j++) {
            if (i != j) {
                term *= (x - X[j]) / (X[i] - X[j]);
            }
        }
        result += term;
    }

    return result;
}

class NewtonPolynomial {
private:
    std::vector<double> X;
    std::vector<double> coefficients;

public:
    NewtonPolynomial(const std::vector<double>& X, const std::vector<double>& Y) {
        this->X = X;
        computeDividedDifferences(Y);
    }

    void computeDividedDifferences(const std::vector<double>& Y) {
        coefficients = Y;

        int n = X.size();
        for (int j = 1; j < n; j++) {
            for (int i = n - 1; i >= j; i--) {
                coefficients[i] = (coefficients[i] - coefficients[i - 1]) / (X[i] - X[i - j]);
            }
        }
    }

    double evaluate(double x) {
        int n = X.size();
        double result = coefficients[n - 1];

        for (int i = n - 2; i >= 0; i--) {
            result = result * (x - X[i]) + coefficients[i];
        }

        return result;
    }
};

class CubicSpline {
private:
    struct SplineTuple {
        double a, b, c, d, x;
    };

    std::vector<SplineTuple> splines;

public:
    void buildSpline(const std::vector<double>& x, const std::vector<double>& y) {
        int n = x.size();
        splines.resize(n);
        std::vector<double> h(n - 1);

        for (int i = 0; i < n - 1; ++i) {
            h[i] = x[i + 1] - x[i];
        }

        numeric::Matrix<double> matrix(n, n);
        std::vector<double> b(n, 0);

        for (int i = 1; i < n - 1; ++i) {
            matrix[i][0] = h[i - 1];
            matrix[i][1] = 2 * (h[i - 1] + h[i]);
            matrix[i][2] = h[i];
            b[i] = 3 * ((y[i + 1] - y[i]) / h[i] - (y[i] - y[i - 1]) / h[i - 1]);
        }

        matrix[0][1] = 1;
        matrix[n - 1][1] = 1;

        std::vector<double> c = numeric::tridiagonalSolve(matrix, b);

        for (int i = 0; i < n - 1; ++i) {
            splines[i].a = y[i];
            splines[i].b = (y[i + 1] - y[i]) / h[i] - h[i] * (c[i + 1] + 2 * c[i]) / 3;
            splines[i].c = c[i];
            splines[i].d = (c[i + 1] - c[i]) / (3 * h[i]);
            splines[i].x = x[i];
        }
    }

    double evaluate(double x) {
        if (splines.empty()) {
            throw std::invalid_argument("Splines not constructed yet");
        }

        const auto segment = std::lower_bound(splines.begin(), splines.end(), x, [](const SplineTuple &s, double x) {
            return s.x < x;
        }) - 1;

        double dx = x - segment->x;
        return segment->a + segment->b * dx + segment->c * dx * dx + segment->d * dx * dx * dx;
    }
};


#endif //POLYNOMS_H

