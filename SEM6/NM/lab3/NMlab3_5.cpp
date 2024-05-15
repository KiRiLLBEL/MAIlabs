#include <iostream>
#include <vector>
#define WITHOUT_NUMPY
#include "Polynoms.h"

using namespace std;
namespace plt = matplotlibcpp;

double f(double x) {
    return x/pow(3*x + 4, 3);
}

int main() {
    double a = -1;
    double b = 1;
    int n = 10;

    double I_rect = rectangleMethod(f, a, b, n);
    double I_trap = trapezoidMethod(f, a, b, n);
    double I_simp = simpsonMethod(f, a, b, n);

    double I_rect_double = rectangleMethod(f, a, b, 2 * n);
    double I_trap_double = trapezoidMethod(f, a, b, 2 * n);
    double I_simp_double = simpsonMethod(f, a, b, 2 * n);

    double err_rect = rungeRomberg(I_rect_double, I_rect, 1);
    double err_trap = rungeRomberg(I_trap_double, I_trap, 1);
    double err_simp = rungeRomberg(I_simp_double, I_simp, 4);

    std::cout << "Integral using Rectangle Method: \n" << "\nFirst: "<< I_rect << "\nSecond: " << I_rect_double << "\nError: " << err_rect << "\n\n";
    std::cout << "Integral using Trapezoid Method: \n" << "\nFirst: "<< I_trap << "\nSecond: " << I_trap_double << "\nError: " << err_trap << "\n\n";
    std::cout << "Integral using Simpson Method: \n" << "\nFirst: "<< I_simp << "\nSecond: " << I_simp_double << "\nError: " << err_simp << "\n\n";
    return 0;
}