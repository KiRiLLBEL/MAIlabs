#include <stdio.h>

#include <math.h>

double f1(double x) {
    return 1 - x + sin(x) - log(1 + x);
}

double f2(double x) {
    return 3 * x - 14 + exp(x) - exp(-1 * x);
}

double f1_d(double x) {
    return -1 + cos(x) - 1 / (1 + x);
}

double f2_d(double x) {
    return 3 + exp(x) + exp(-1 * x);
}

double f1_v(double x) {
    return 1 + sin(x) - log(1 + x);
}

double f2_v(double x) {
    return log(14 - 3 * x + exp(-1 * x));
}

double dichotomy(double (*f)(double x), double eps, double a, double b) {

    double buf;

    while (!(fabs(a - b) < eps)) {

        if (f(a) * f((a + b) / 2) > 0) {
            a = (a + b) / 2;
        } else {
            b = (a + b) / 2;
        }
    }
    return (a + b) / 2;
}

double iter(double (*f)(double x), double eps, double a, double b) {

    double x = (a + b) / 2;
    double x_n = f(x);

    while (!(fabs(x_n - x) < eps)) {
        x = f(x);
        x_n = f(x);
    }

    return x;
}

double newton(double (*f)(double x), double (*f_d)(double x), double eps, double a, double b) {

    double x = (a + b) / 2;
    while (!(fabs(f(x) / f_d(x)) < eps)) {

        x = x - f(x) / f_d(x);
    }
    return x;
}

int main(void) {

    double eps;

    scanf("%lf", &eps);
    printf("Точность: %.16f\n", eps);
    printf("+---------------------------------+---------+---------------+-----------------------+-----------+----------+---------+\n");
    printf("|            Уравнение            | Отрезок | Базовый метод | Прибл. значение корня | Дихотомии | Итераций | Ньютона |\n");
    printf("+---------------------------------+---------+---------------+-----------------------+-----------+----------+---------+\n");
    printf("| 1 - x + sin(x) - ln(1 + x) = 0  | [1, 1.5]|    Итераций   |         1.1474        |   %.4f  |  %.4f  |  %.4f |\n", dichotomy(f1, eps, 1, 1.5), iter(f1_v, eps, 1, 1.5),newton(f1, f1_d, eps, 1, 1.5));
    printf("+---------------------------------+---------+---------------+-----------------------+-----------+----------+---------+\n");
    printf("|  3 * x - 14 + exp(x) - exp(-x)  |  [1, 3] |    Ньютона    |         2.0692        |   %.4f  |  %.4f  |  %.4f |\n", dichotomy(f2, eps, 1, 3), iter(f2_v, eps, 1, 3), newton(f2, f2_d, eps, 1, 3));
    printf("+---------------------------------+---------+---------------+-----------------------+-----------+----------+---------+\n");

    return 0;
}