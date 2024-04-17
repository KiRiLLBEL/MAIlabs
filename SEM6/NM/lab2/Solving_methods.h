#ifndef SOLVING_METHODS_H
#define SOLVING_METHODS_H
#include <functional>
#include <stdexcept>
#include <utility>
#include <iostream>

double find_q(const std::function<double(double, double)>& phi_d, double a, double b, double lambda) {
    double q = -1e9;
    double x = a;
    while(x <= b) {
        q = std::max(q, std::abs(phi_d(x, lambda)));
        x += 0.01;
    }
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
    do {
        double x_next = f(x_cur, lambda);
        continueIteration = q / (1.0 - q) * std::abs(x_next - x_cur);
        x_cur = x_next;
    } while (continueIteration > eps);

    return x_cur;
}

double newtonMethod(const std::function<double(double)>& f, const std::function<double(double)>& f_d, const std::function<double(double)>& f_dd,double a, double b, double eps) {
    double x0 = a;
    if (!(f(x0) * f_dd(x0) > eps)) {
        x0 = b;
    }
    double x_cur = x0;
    double dx = 1.0;
    do {
        double x_next = x_cur - f(x_cur) / f_d(x_cur);
        dx = std::abs(x_next - x_cur);
        x_cur = x_next;
    } while (dx > eps);
    return x_cur;
}

#endif //SOLVING_METHODS_H
