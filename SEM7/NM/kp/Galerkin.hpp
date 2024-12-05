#include <functional>
#include <vector>
#include "../../../SEM6/NM/lab1/Matrix.h"

#include <QMainWindow>

using Basis = std::vector<std::function<double(double)>>;

struct GalerkinConfig
{
    int N;
    double a;
    double b;
    int T;
    double dt;
    int L;
    double dx;
};

Basis generateBasis(const std::function<double(double)>& startFunc, const GalerkinConfig& config);

Basis generateBasisDeriv2(const std::function<double(double)>& startFunc, const GalerkinConfig& config);

std::vector<double> initialCondition(const std::function<double(double)>& initFunc, const Basis& phi, const GalerkinConfig& config);

std::vector<std::vector<double>> GalerkinSolve(const std::vector<double>& initCoeffs, const Basis& phi, const Basis& dphi2, const GalerkinConfig& config);

std::vector<std::vector<double>> true_calculation(
    std::function<double(double, double)> f,
    GalerkinConfig& config);

std::vector<std::vector<double>> galerkin_calculation(
    std::vector<std::vector<double>> coeffs,
    const Basis& basis,
    GalerkinConfig& config);

QWidget* create2DGraphWithSlider(const std::vector<std::vector<double>>& data1, const std::vector<std::vector<double>>& data2);
QWidget* create2DGraphWithError(const std::vector<std::vector<double>>& data1, const std::vector<std::vector<double>>& data2);