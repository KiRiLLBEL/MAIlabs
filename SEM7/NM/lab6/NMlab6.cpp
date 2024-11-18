#include <cmath>
#include <matplot/matplot.h>
#include "hyperbolic.h"

auto U_xt = [](double x, double t, double a = 1){
    return cos(x) * sin(2 * t);
};

auto u_0t = [](double t, double a = 1) {
    return sin(2 * t);
};

auto u_pit = [](double t, double a = 1) {
    return -sin(2 * t);
};

auto u_x0 = [](double x) {
    return 0;
};

auto ut_x0 = [](double x) {
    return 2 * cos(x);
};

int main() {
    SchemeConfig config {
        .N = 10,
        .K = 100,
        .dx = M_PI / 10,
        .dt = 1.0 / 100
    };
    auto u0 = firstLayer(u_x0, config);
    auto u1 = secondLayer(u_x0, ut_x0, config);
    auto result1 = explicit_scheme(u0, u1, u_0t, u_pit, config);
    auto result2 = implicit_scheme(u0, u1, u_0t, u_pit, config);
    auto true_value = true_calculation(U_xt, config);
    int t = 2;
    visualize(true_value, result1, result2, config, t);
    plot_error_over_x(true_value, result1, result2,  config, t);

    int N_min = 10;
    int N_max = 100;
    int N_step = 5;
    int K_min = 100;
    int K_max = 1000;
    int K_step = 10;
    matplot::show();
    // plot_error_3d(EXPLICIT, explicit_scheme, U_xt, u_x0, u_0t, u_pit, config, N_min, N_max, N_step, K_min, K_max, K_step, "Явная схема");
    // matplot::show();
    // plot_error_3d(IMPLICIT, implicit_scheme, U_xt, u_x0, u_0t, u_pit, config, N_min, N_max, N_step, K_min, K_max, K_step, "Неявная схема");
    // matplot::show();
    return 0;
}