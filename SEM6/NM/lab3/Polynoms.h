#ifndef POLYNOMS_H
#define POLYNOMS_H

#include <vector>
#include <algorithm>
#include "../lab1/Matrix.h"
#include <matplotlibcpp.h>

namespace plt = matplotlibcpp;
using namespace numeric;


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
    CubicSpline(const std::vector<double>& x, const std::vector<double>& y) : splines(x.size() - 1){
        int n = x.size() - 1;
        std::vector<double> h(n);

        for (int i = 0; i < n; ++i) {
            h[i] = x[i + 1] - x[i];
        }

        numeric::Matrix<double> matrix(n, n);
        std::vector<double> b(n, 0);

        for (int i = 1; i <= n - 1; ++i) {
            if(i == 1) {
                matrix[i][i] = 2 * (h[i - 1] + h[i]);
                matrix[i][i + 1] = h[i];
            } else if(i == n - 1) {
                matrix[i][i - 1] = h[i - 1];
                matrix[i][i] = 2 * (h[i - 1] + h[i]);
            } else {
                matrix[i][i - 1] = h[i - 1];
                matrix[i][i] = 2 * (h[i - 1] + h[i]);
                matrix[i][i + 1] = h[i];
            }
            b[i] = 3 * ((y[i + 1] - y[i]) / h[i] - (y[i] - y[i - 1]) / h[i - 1]);
        }
        matrix[0][0] = 1;

        std::vector<double> c = numeric::tridiagonalSolve(matrix, b);

        for (int i = 0; i < n; ++i) {
            splines[i].a = y[i];
            if(i == n - 1) {
                splines[i].b = (y[n] - y[n - 1]) / h[i] - 2.0 / 3 * h[i] * c[i];
                splines[i].d = - c[i] / (3 * h[i]);
            } else {
                splines[i].b = (y[i + 1] - y[i]) / h[i] - h[i] * (c[i + 1] + 2 * c[i]) / 3;
                splines[i].d = (c[i + 1] - c[i]) / (3 * h[i]);
            }
            splines[i].c = c[i];
            splines[i].x = x[i];
        }
    }

    double evaluate(double x) const{
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

void plotCubicSpline(const CubicSpline& sp, const std::vector<double>& x_points, const std::vector<double>& y_points) {
    std::vector<double> x_vals, y_vals;

    double x_min = *min_element(x_points.begin(), x_points.end());
    double x_max = *max_element(x_points.begin(), x_points.end());
    double step = (x_max - x_min) / 1000;  // Подробность графика

    for (double x = x_min; x <= x_max; x += step) {
        double y = sp.evaluate(x);
        x_vals.push_back(x);
        y_vals.push_back(y);
    }
    plt::scatter(x_points, y_points, 40);
    plt::plot(x_vals, y_vals); // Рисуем сплайн
    plt::title("Cubic Spline Interpolation");
    plt::xlabel("X");
    plt::ylabel("Y");
    plt::grid(true);
    plt::show();
}

template<typename T>
Matrix<T> vandermonde(const std::vector<T>& x, int degree) {
    size_t n = x.size();
    Matrix<T> V(n, degree + 1);
    for (size_t i = 0; i < n; ++i) {
        T val = 1;
        for (int j = 0; j <= degree; ++j) {
            V[i][j] = val;
            val *= x[i];
        }
    }
    return V;
}

template<typename T>
Matrix<T> leastSquares(const std::vector<T>& x, const std::vector<T>& y, int degree) {
    Matrix<T> V = vandermonde(x, degree);
    auto Vt = V.transpose();
    Matrix<T> VtV = Vt * V;
    std::vector<T> VtY = Vt * y;

    // Создание аугментированной матрицы VtV | VtY
    Matrix<T> augmented(VtV.rows(), VtV.cols() + 1);
    for (size_t i = 0; i < VtV.rows(); ++i) {
        for (size_t j = 0; j < VtV.cols(); ++j) {
            augmented[i][j] = VtV[i][j];
        }
        augmented[i][VtV.cols()] = VtY[i];
    }

    LUMatrix<T> luSolver(augmented);
    Matrix<T> ans = luSolver.solve();
    return ans;
}

double derivativeUsingQuadraticInterpolation(const std::vector<double>& X, const std::vector<double>& Y, double x) {
    int n = X.size();
    if (n < 3) {
        throw std::invalid_argument("Need at least three points for quadratic interpolation.");
    }

    int i = 1;
    for (; i < n - 1; i++) {
        if (X[i] <= x && X[i+1] > x) {
            break;
        }
    }
    if (i == n - 1) {
        throw std::invalid_argument("x is out of bounds of the provided data points.");
    }

    double dy = (Y[i+1] - Y[i-1]) / (X[i+1] - X[i-1]) +
                (2 * x - X[i] - X[i+1]) * (
                        (Y[i+1] - Y[i]) / (X[i+1] - X[i]) -
                        (Y[i] - Y[i-1]) / (X[i] - X[i-1])
                ) / (X[i+1] - X[i-1]);

    return dy;
}

double linearDerivative(const std::vector<double>& X, const std::vector<double>& Y, double x) {
    int n = X.size();
    if (n < 2) {
        throw std::invalid_argument("Need at least two points for linear interpolation.");
    }

    int i = 0;
    for (; i < n - 1; i++) {
        if (x >= X[i] && x <= X[i+1]) {
            break;
        }
    }
    if (i == n - 1) {
        throw std::invalid_argument("x is out of the bounds of the provided data points.");
    }

    double dy = (Y[i+1] - Y[i]) / (X[i+1] - X[i]);

    return dy;
}

double secondDerivativeAtX(const std::vector<double>& X, const std::vector<double>& Y, double x) {
    int n = X.size();
    if (n < 3) {
        throw std::invalid_argument("Need at least three points for quadratic interpolation.");
    }

    // Найти подходящий интервал i так, что x_i <= x < x_{i+1}
    int i = 1;
    for (; i < n - 1; i++) {
        if (X[i] <= x && x < X[i + 1]) {
            break;
        }
    }
    if (i == 1 || i == n - 1) {
        throw std::invalid_argument("x is out of the interpolation bounds. Need more internal data points.");
    }

    double h1 = X[i] - X[i-1];
    double h2 = X[i+1] - X[i];
    double delta1 = (Y[i] - Y[i-1]) / h1;
    double delta2 = (Y[i+1] - Y[i]) / h2;

    double second_derivative = 2 * (delta2 - delta1) / (h2 + h1);

    return second_derivative;
}

double rectangleMethod(std::function<double(double)> f, double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += f(a + i * h);
    }
    return sum * h;
}

double trapezoidMethod(std::function<double(double)> f, double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));
    for (int i = 1; i < n; i++) {
        sum += f(a + i * h);
    }
    return sum * h;
}

double simpsonMethod(std::function<double(double)> f, double a, double b, int n) {
    double h = (b - a) / n;
    double sum = f(a) + f(b);
    for (int i = 1; i < n; i++) {
        sum += (i % 2 == 0 ? 2 : 4) * f(a + i * h);
    }
    return sum * h / 3;
}

double rungeRomberg(double I1, double I2, int k) {
    return (I1 - I2) / (pow(2, k) - 1);
}

#endif //POLYNOMS_H

