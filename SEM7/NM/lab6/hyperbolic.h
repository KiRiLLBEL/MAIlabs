#pragma once

#include <vector>
#include <functional>
#include <string>

#include <QMainWindow>

struct SchemeConfig {
    int N;
    int K;
    double dx;
    double dt;
    double a = 1;
};

std::vector<double> firstLayer(std::function<double(double)> start_x, SchemeConfig& config);
std::vector<double> secondLayer(
    std::function<double(double)> psi1, 
    std::function<double(double)> psi2, 
    SchemeConfig& config);

std::vector<std::vector<double>> true_calculation(
    std::function<double(double, double, double)> f,
    SchemeConfig& config);

std::vector<std::vector<double>> explicit_scheme(
    std::vector<double>& start1,
    std::vector<double>& start2,
    std::function<double(double, double)> guard_start, 
    std::function<double(double, double)> guard_end, 
    SchemeConfig& config);

std::vector<std::vector<double>> implicit_scheme(
    std::vector<double>& start1,
    std::vector<double>& start2,
    std::function<double(double, double)> guard_start, 
    std::function<double(double, double)> guard_end, 
    SchemeConfig& config);

QWidget* visualize(
    const std::vector<std::vector<double>>& true_value, 
    const std::vector<std::vector<double>>& data1, 
    const std::vector<std::vector<double>>& data2,
    SchemeConfig& config, int time);

QWidget* plot_error_over_x(
    const std::vector<std::vector<double>>& true_value,
    const std::vector<std::vector<double>>& data1,
    const std::vector<std::vector<double>>& data2,
    SchemeConfig& config, int time);

enum SchemeType {
    EXPLICIT,
    IMPLICIT,
    KRANK_NIKOLSON
};

QWidget* plot_error_3d_hyperbolic(
    SchemeType type,
    const std::function<std::vector<std::vector<double>>(std::vector<double>&, std::vector<double>&, std::function<double(double, double)>, std::function<double(double, double)>, SchemeConfig&)>& scheme_function,
    const std::function<double(double, double, double)>& analytical_solution,
    std::function<double(double)> initial_condition,
    std::function<double(double)> initial_velocity,
    std::function<double(double, double)> guard_start,
    std::function<double(double, double)> guard_end,
    SchemeConfig& config,
    int N_min, int N_max, int N_step,
    int K_min, int K_max, int K_step);