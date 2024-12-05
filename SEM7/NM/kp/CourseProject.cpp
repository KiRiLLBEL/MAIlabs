#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QTabWidget>

#include <cmath>

#include "Galerkin.hpp" 

auto u0t = [](double x) -> double
{
    return sin(2 * M_PI * x);
};

auto uxt = [](double x, double t) -> double
{
    return exp(-4 * M_PI * M_PI * t) * sin(2 * M_PI * x);
};

auto main(int argc, char *argv[]) -> int {
    QApplication app(argc, argv);
    QMainWindow window;

    GalerkinConfig config {
        .N = 4,
        .a = 0,
        .b = 1,
        .T = 10,
        .dt = 0.1 / 11.0,
        .L = 100,
        .dx = 1.0 / 101.0
    };


    QWidget *centralWidget = new QWidget(&window);
    window.setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    centralWidget->setLayout(layout);

    QTabWidget *tabWidget = new QTabWidget(centralWidget);
    layout->addWidget(tabWidget);

    auto basicFunction = [](double x){ return sin(M_PI * x);};
    auto basis = generateBasis(basicFunction, config);
    auto basisDeriv2 = generateBasisDeriv2(basicFunction, config);
    auto aVectorStart = initialCondition(u0t, basis, config);
    auto coeffs = GalerkinSolve(aVectorStart, basis, basisDeriv2, config);

    auto trueData = true_calculation(uxt, config);
    auto galerkinData = galerkin_calculation(coeffs, basis, config);
    
    auto* Graphics = create2DGraphWithSlider(trueData, galerkinData);
    tabWidget->addTab(Graphics, "Graphics");

    auto* Errors = create2DGraphWithError(trueData, galerkinData);
    tabWidget->addTab(Errors, "Errors");

    window.resize(1024, 768);
    window.show();

    return app.exec();
}