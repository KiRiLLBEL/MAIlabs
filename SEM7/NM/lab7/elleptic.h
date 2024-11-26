#pragma once
#include <QMainWindow>
#include <functional>
#include <vector>

struct SchemeDimensionConfig
{
    int N;
    int M;
    double dy;
    double dx;
};

using functionD = const std::function<double(double)>&;
using functionDD = const std::function<double (double, double)>&;

std::vector<std::vector<double>> startIteration(
    functionD u0y, 
    functionD u1y, 
    functionD uyx0, 
    functionD uyxpi, 
    const SchemeDimensionConfig& config);

std::vector<std::vector<double>> true_calculation(functionDD realFunction, SchemeDimensionConfig &config);

QWidget* create3DGraph(const std::vector<std::vector<double>>& data);