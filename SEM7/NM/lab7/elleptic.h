#pragma once
#include <QMainWindow>
#include <functional>
#include <vector>

#include "../../../SEM6/NM/lab1/Matrix.h"

struct SchemeDimensionConfig
{
    int N;
    int M;
    double Ly;
    double Lx;
    double dy;
    double dx;
};

using functionD = const std::function<double(double)>&;
using functionDD = const std::function<double (double, double)>&;

template<class T>
using Solver = const std::function<std::vector<T>(const numeric::AbstractMatrix<T> &, const std::vector<T> &, T, size_t)>&;

std::vector<std::vector<double>> startIteration(
    functionD u0y, 
    functionD u1y, 
    functionD uyx0, 
    functionD uyxpi, 
    Solver<double> solver,
    const SchemeDimensionConfig& config);

std::vector<std::vector<double>> true_calculation(functionDD realFunction, SchemeDimensionConfig &config);

QWidget* create3DGraph(const std::vector<std::vector<double>>& data);

QWidget* createAbsoluteErrorGraph(const std::vector<std::vector<double>>& trueData, const std::vector<std::vector<double>>& iterationData, const QString& methodName);

QWidget* createL2ErrorGraph(
    const std::vector<std::vector<double>>& trueData,
    functionD u0y, functionD u1y, functionD uyx0, functionD uyxpi,
    Solver<double> solver,
    SchemeDimensionConfig config
);