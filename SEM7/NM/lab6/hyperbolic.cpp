#include "hyperbolic.h"
#include <vector>
#include <functional>
#include <matplot/matplot.h>

#include "../../../SEM6/NM/lab1/Matrix.h"
using namespace numeric;

std::vector<double> firstLayer(std::function<double(double)> start_x, SchemeConfig& config) {
    std::vector<double> start_pos(config.N);
    for(int i = 0; i < config.N; ++i) {
        double x = i * config.dx;
        start_pos[i] = start_x(x);
    }
    return start_pos;
}

std::vector<double> secondLayer(
    std::function<double(double)> psi1, 
    std::function<double(double)> psi2, 
    SchemeConfig& config) {
    std::vector<double> start_pos(config.N);
    for(int i = 0; i < config.N; ++i) {
        double x = i * config.dx;
        start_pos[i] = psi1(x) + psi2(x) * config.dt;
    }
    return start_pos;
}

std::vector<std::vector<double>> true_calculation(
    std::function<double(double, double, double)> f,
    SchemeConfig& config) {
    std::vector<std::vector<double>> results;
    for(int i = 0; i < config.K; ++i) {
        double t = i * config.dt;
        std::vector<double> f_current(config.N);
        for(int j = 0; j < config.N; ++j) {
            double x = j * config.dx;
            f_current[j] = f(x, t, config.a);
        }
        results.push_back(f_current);
    }
    return results;;
}

std::vector<std::vector<double>> explicit_scheme(
    std::vector<double>& start1,
    std::vector<double>& start2,
    std::function<double(double, double)> guard_start, 
    std::function<double(double, double)> guard_end, 
    SchemeConfig& config) {
    auto sigma = config.a * config.a * config.dt * config.dt / (config.dx * config.dx);
    

    std::vector<std::vector<double>> results;
    std::vector<double> prev = start1;
    std::vector<double> current = start2;
    std::vector<double> next(config.N);
    results.push_back(prev);
    results.push_back(current);
    for(int i = 0; i < config.K; ++i) {
        double t = i * config.dt;
        next[0] = guard_start(t + config.dt, config.a);
        next[config.N - 1] = guard_end(t + config.dt, config.a);

        for(int j = 1; j < config.N - 1; ++j) {
            next[j] = 
                current[j + 1] * sigma + 
                current[j] * (-2 * sigma + 2 - 3 * config.dt * config.dt) + 
                current[j - 1] * sigma -
                prev[j];
        }
        prev = current;
        current = next;
        results.push_back(current);
    }
    return results;
}

std::vector<std::vector<double>> implicit_scheme(
    std::vector<double>& start1,
    std::vector<double>& start2,
    std::function<double(double, double)> guard_start, 
    std::function<double(double, double)> guard_end, 
    SchemeConfig& config) {
    std::vector<std::vector<double>> results;
    std::vector<double> u_prev = start1;
    std::vector<double> u_cur = start2;
    std::vector<double> u_new(config.N);
    results.push_back(u_prev);
    results.push_back(u_cur);

    Matrix<double> matrix(config.N, config.N);
    std::vector<double> d(config.N);

    double A = -config.a / config.dx / config.dx;
    double B = 2 * config.a / config.dx / config.dx + 1 / (config.dt * config.dt) + 3;
    double C = -config.a / config.dx / config.dx;

    for (int i = 0; i < config.K; ++i) {
        double t = (i + 1) * config.dt;
        for (size_t j = 0; j < config.N; ++j) {
            if (j == 0) {
                matrix[j][j] = 2 * config.a / config.dx + config.dx / config.dt + 3 * config.dx;
                matrix[j][j + 1] = -2 * config.a / config.dx;
                d[j] = (2 * u_cur[j] - u_prev[j]) / config.dt * config.dt - A * guard_start(t, config.a);
            } else if (j == config.N - 1) {
                matrix[j][j - 1] =  -2 * config.a / config.dx;
                matrix[j][j] = 2 * config.a / config.dx + config.dx / config.dt + 3 * config.dx;
                d[j] = (2 * u_cur[j] - u_prev[j]) / config.dt * config.dt - C * guard_end(t, config.a);
            } else {
                d[j] = (2 * u_cur[j] - u_prev[j]) / config.dt * config.dt;
                matrix[j][j - 1] = A;
                matrix[j][j] = B;
                matrix[j][j + 1] = C;
            }
        }

        // Решаем систему уравнений
        u_new = tridiagonalSolve(matrix, d);
        u_prev = u_cur;
        u_cur = u_new;
        results.push_back(u_cur);
    }
    return results;
}

void visualize(
    const std::vector<std::vector<double>>& true_value, 
    const std::vector<std::vector<double>>& data1, 
    const std::vector<std::vector<double>>& data2,
    SchemeConfig& config, int time) {
    std::vector<double> x(config.N);
    for (int i = 0; i < config.N; ++i) {
        x[i] = i * config.dx;
    }
    auto f1 = matplot::figure();
    matplot::figure(f1);
    matplot::hold(matplot::on);
    auto p = matplot::plot(x, data1[time], x, data2[time], x, true_value[time]);
    matplot::title("Схема в момент времени t = " + std::to_string(time * config.dt));
    p[0]->display_name("Явная схема");
    p[1]->display_name("Неявная схема");
    p[2]->display_name("Аналитическое решение");
    matplot::hold(matplot::off);
    ::matplot::legend(matplot::off);
    matplot::xlabel("x");
    matplot::ylabel("U");
}
void plot_error_over_x(
    const std::vector<std::vector<double>>& true_value,
    const std::vector<std::vector<double>>& data1,
    const std::vector<std::vector<double>>& data2,
    SchemeConfig& config, int time) {
    std::vector<double> x(config.N);
    for (int i = 0; i < config.N; ++i) {
        x[i] = i * config.dx;
    }

    std::vector<double> error1(config.N);
    std::vector<double> error2(config.N);

    for (int i = 0; i < config.N; ++i) {
        error1[i] = std::abs(true_value[time][i] - data1[time][i]);
        error2[i] = std::abs(true_value[time][i] - data2[time][i]);
    }
    auto f2 = matplot::figure();
    matplot::figure(f2);
    matplot::hold(matplot::on);
    auto p = matplot::plot(x, error1, x, error2);
    matplot::title("Погрешность в момент времени t = " + std::to_string(time * config.dt));
    p[0]->display_name("Погрешность явной схемы");
    p[1]->display_name("Погрешность неявной схемы");
    matplot::hold(matplot::off);
    ::matplot::legend(matplot::off);
    matplot::xlabel("x");
    matplot::ylabel("Погрешность");
}

// void plot_error_3d(
//     SchemeType type,
//     const std::function<std::vector<std::vector<double>>(std::vector<double>&, std::vector<double>&, std::function<double(double, double)>, std::function<double(double, double)>, SchemeConfig&)>& scheme_function,
//     const std::function<double(double, double, double)>& analytical_solution,
//     std::function<double(double)> initial_condition,
//     std::function<double(double, double)> guard_start, 
//     std::function<double(double, double)> guard_end, 
//     SchemeConfig& config,
//     int N_min, int N_max, int N_step,
//     int K_min, int K_max, int K_step,
//     const std::string& filename) {

//     std::vector<double> N_values;
//     std::vector<double> K_values;
//     std::vector<double> errors;

//     int original_N = config.N;
//     double original_dx = config.dx;
//     int original_K = config.K;
//     double original_dt = config.dt;

//     for (int N = N_min; N <= N_max; N += N_step) {
//         for (int K = K_min; K <= K_max; K += K_step) {
//             config.N = N;
//             config.dx = M_PI / (N - 1);
//             config.K = K;
//             config.dt = 1.0 / K;

//             if (type == EXPLICIT) {
//                 double alpha = (config.a * config.dt) / (config.dx * config.dx);
//                 if (alpha > 0.5) {
//                     continue;
//                 }
//             }

//             auto u0 = firstLayer(initial_condition, config);

//             auto true_value = true_calculation(analytical_solution, config);

//             auto result = scheme_function(u0, guard_start, guard_end, config);

//             double total_error = 0.0;
//             int total_points = config.K * config.N;

//             for (int k = 0; k < config.K; ++k) {
//                 for (int i = 0; i < config.N; ++i) {
//                     total_error += std::abs(true_value[k][i] - result[k][i]);
//                 }
//             }

//             double avg_error = total_error / total_points;

//             N_values.push_back(N);
//             K_values.push_back(K);
//             errors.push_back(avg_error);
//         }
//     }

//     config.N = original_N;
//     config.dx = original_dx;
//     config.K = original_K;
//     config.dt = original_dt;


//     auto [N_mesh, K_mesh] = matplot::meshgrid(matplot::unique(N_values), matplot::unique(K_values));
//     std::vector<std::vector<double>> errors_mesh(K_mesh.size(), std::vector<double>(N_mesh[0].size(), 0.0));

// for (size_t k = 0; k < K_mesh.size(); ++k) {
//         for (size_t n = 0; n < N_mesh[0].size(); ++n) {

//             for (size_t i = 0; i < N_values.size(); ++i) {
//                 if (N_values[i] == N_mesh[0][n] && K_values[i] == K_mesh[k][0]) {
//                     errors_mesh[k][n] = errors[i];
//                     break;
//                 }
//             }
//         }
//     }

//     auto fig = matplot::figure();
//     matplot::figure(fig);
//     matplot::surf(N_mesh, K_mesh, errors_mesh);
//     matplot::xlabel("N");
//     matplot::ylabel("K");
//     matplot::zlabel("Ошибка");
//     matplot::title(filename);
// };