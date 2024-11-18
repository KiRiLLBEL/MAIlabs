#include <cmath>
#include <matplot/matplot.h>
#include "parabolic.h"

auto U_xt = [](double x, double t, double a = 1){
    return exp(-a * t) * cos(x);
};

auto u_0t = [](double t, double a = 1) {
    return exp(-a * t);
};

auto u_pit = [](double t, double a = 1) {
    return -exp(-a * t);
};

auto u_x0 = [](double x) {
    return cos(x);
};

int main() {
    SchemeConfig config {
        .N = 10,
        .K = 100,
        .dx = M_PI / 10,
        .dt = 1.0 / 100
    };
    auto u0 = start(u_x0, config);
    auto result1 = explicit_scheme(u0, u_0t, u_pit, config);
    auto result2 = implicit_scheme(u0, u_0t, u_pit, config);
    auto result3 = krank_nikolson_scheme(u0, u_0t, u_pit, config);
    auto true_value = true_calculation(U_xt, config);
    int t = 50;
    visualize(true_value, result1, result2, result3, config, t);
    plot_error_over_x(true_value, result1, result2, result3, config, t);

    int N_min = 10;
    int N_max = 100;
    int N_step = 5;
    int K_min = 100;
    int K_max = 1000;
    int K_step = 10;
    matplot::show();
    plot_error_3d(EXPLICIT, explicit_scheme, U_xt, u_x0, u_0t, u_pit, config, N_min, N_max, N_step, K_min, K_max, K_step, "Явная схема");
    plot_error_3d(IMPLICIT, implicit_scheme, U_xt, u_x0, u_0t, u_pit, config, N_min, N_max, N_step, K_min, K_max, K_step, "Неявная схема");
    plot_error_3d(KRANK_NIKOLSON, krank_nikolson_scheme, U_xt, u_x0, u_0t, u_pit, config, N_min, N_max, N_step, K_min, K_max, K_step, "Кранке-Никольсона");
    return 0;
}