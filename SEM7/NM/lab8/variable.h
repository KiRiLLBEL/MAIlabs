#pragma once

#include <vector>
#include <functional>
#include <QMainWindow>


struct SchemeDimensionTimeConfig
{
    int N;
    int M;
    int K;
    double Lx;
    double Ly;
    double Lt;
    double dx;
    double dy;
    double dt;
};


using Tensor = std::vector<std::vector<std::vector<double>>>;
using FunctionDDD = const std::function<double(double, double, double)>&;
using FunctionDD = const std::function<double(double, double)>&;

Tensor true_calculation(FunctionDDD realFunction, SchemeDimensionTimeConfig& config);
Tensor variadic_ways(
    FunctionDD phi1,
    FunctionDD phi2,
    FunctionDD phi3,
    FunctionDD phi4,
    FunctionDD psi,
    SchemeDimensionTimeConfig& config);

Tensor decimal_steps(
    FunctionDD phi1,
    FunctionDD phi2,
    FunctionDD phi3,
    FunctionDD phi4,
    FunctionDD psi,
    SchemeDimensionTimeConfig& config);

QWidget* createTensorGraph(const Tensor& tensorData, const QString& methodName);

QWidget* createErrorGraph(
    const Tensor& trueValue, 
    const Tensor& dataValue, 
    const QString& methodName);

QWidget* createErrorGraphForDifferentMethods(
    FunctionDDD realFunction, 
    FunctionDD phi1, FunctionDD phi2, FunctionDD phi3, FunctionDD phi4, FunctionDD psi,
    SchemeDimensionTimeConfig& config);