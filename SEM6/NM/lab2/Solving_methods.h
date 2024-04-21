#ifndef SOLVING_METHODS_H
#define SOLVING_METHODS_H
#include <functional>
#include <stdexcept>
#include <utility>
#include <iostream>
#include "../lab1/Matrix.h"
using namespace numeric;

double find_q(const std::function<double(double, double)>& phi_d, double a, double b, double lambda) {
    double q = -1e9;
    double x = a;
    while(x <= b) {
        q = std::max(q, std::abs(phi_d(x, lambda)));
        x += 0.01;
    }
    return q;
}

double find_q(
        const numeric::Matrix<std::function<double(const std::vector<double>&)>>& phi_d,
        const std::vector<double>& a,
        const std::vector<double>& b,
        double step = 0.01
) {
    if (a.size() != b.size() || a.size() == 0) {
        throw std::invalid_argument("Invalid dimension boundaries or empty boundaries provided.");
    }

    size_t n = a.size();
    std::vector<double> x(n);
    double q = 0;

    std::function<void(size_t)> iterate = [&](size_t dim) {
        if (dim == n) {
            numeric::Matrix<double> values(phi_d.rows(), phi_d.cols());
            for (size_t i = 0; i < phi_d.rows(); ++i) {
                for (size_t j = 0; j < phi_d.cols(); ++j) {
                    values[i][j] = std::abs(phi_d[i][j](x));
                }
            }

            for (size_t i = 0; i < values.rows(); ++i) {
                double row_sum = 0;
                for (size_t j = 0; j < values.cols(); ++j) {
                    row_sum += values[i][j];
                }
                q = std::max(q, row_sum);
            }
        } else {
            for (double v = a[dim]; v <= b[dim]; v += step) {
                x[dim] = v;
                iterate(dim + 1);
            }
        }
    };

    iterate(0);

    return q;
}

double iterationMethod(const std::function<double(double, double)>& f, const std::function<double(double, double)>& f_d, double a, double b, double x0, double lambda, double eps) {
    double q = find_q(f_d, a, b, lambda);
    if(q >= 1) {
        std::cout << q << "\n";
        throw std::invalid_argument("Function is not valid");
    }
    double x_cur = x0;
    double continueIteration = 1.0;
    int countOfIterations = 0;
    do {
        double x_next = f(x_cur, lambda);
        continueIteration = q / (1.0 - q) * std::abs(x_next - x_cur);
        x_cur = x_next;
        ++countOfIterations;
    } while (continueIteration > eps);
    std::cout << "Iterations count: " << countOfIterations << "\n";
    return x_cur;
}

double newtonMethod(const std::function<double(double)>& f, const std::function<double(double)>& f_d, const std::function<double(double)>& f_dd,double a, double b, double eps) {
    double x0 = a;
    if (!(f(x0) * f_dd(x0) > eps)) {
        x0 = b;
    }
    double x_cur = x0;
    double dx = 1.0;
    int countOfIterations = 0;
    do {
        double x_next = x_cur - f(x_cur) / f_d(x_cur);
        dx = std::abs(x_next - x_cur);
        x_cur = x_next;
        ++countOfIterations;
    } while (dx > eps);
    std::cout << "Iterations count: " << countOfIterations << "\n";
    return x_cur;
}

std::vector<double> iterationMethodSystem(
        const std::vector<std::function<double(const std::vector<double>&)>>& F,
        const numeric::Matrix<std::function<double(const std::vector<double>&)>>& J,
        const std::vector<double>& initial_guess,
        const std::vector<double>& a,
        const std::vector<double>& b,
        double eps) {
    std::vector<double> x = initial_guess;
    std::vector<double> x_next = initial_guess;
    std::size_t n = initial_guess.size();
    bool converged = true;
    double q = find_q(J, a, b);
    if(q >= 1) {
        std::cout << q << "\n";
        throw std::invalid_argument("Function is not valid");
    }
    while (converged) {
        for (size_t i = 0; i < n; ++i) {
            x_next[i] = F[i](x);
        }

        if (numeric::norm((q / (1.0 - q)) * numeric::diffVector(x_next, x)) < eps) {
            converged = false;
        }

        x = x_next;
    }

    return x;
}

std::vector<double> newtonMethodLU(
        const std::vector<std::function<double(const std::vector<double>&)>>& F,
        const Matrix<std::function<double(const std::vector<double>&)>>& J,
        const std::vector<double>& initialGuess,
        double eps
) {
    std::vector<double> x = initialGuess;
    size_t n = x.size();

    bool continueIteration = true;
    while(continueIteration) {
        std::vector<double> Fx(n);
        for (size_t i = 0; i < n; ++i) {
            Fx[i] = F[i](x);
        }

        Matrix<double> Jx(n, n + 1);
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                Jx[i][j] = J[i][j](x);
            }
            Jx[i][n] = -Fx[i];
        }

        LUMatrix<double> lu(Jx);
        Matrix<double> dx = lu.solve();

        for (size_t i = 0; i < n; ++i) {
            x[i] += dx[0][i];
        }

        if (norm(dx[0]) < eps) {
            continueIteration = false;
        }
    }

    return x;
}
#endif //SOLVING_METHODS_H
