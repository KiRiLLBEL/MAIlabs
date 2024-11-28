#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QTabWidget>

#include <cmath>

#include "variable.h"

auto U_xyt = [](double x, double y, double t)
{
    return cos(2 * x) * cosh(y) * exp(-3 * t);
};

auto phi1 = [](double y, double t) 
{
    return cosh(y) * exp(-3 * t);
};

auto phi2 = [](double y, double t)
{
    return 0.0;
};

auto phi3 = [](double x, double t)
{
    return cos(2 * x) * exp(-3 * t);
};

auto phi4 = [](double x, double t)
{
    return (5.0 / 4.0) * cos(2 * x) * exp(-3 * t);
};

auto psi = [](double x, double y)
{
    return cos(2 * x) * cosh(y);
};

auto main(int argc, char *argv[]) -> int {
    QApplication app(argc, argv);
    QMainWindow window;

    int N = 25;
    int M = 25;
    int K = 25;
    double Lx = M_PI_4;
    double Ly = log(2);
    double Lt = 1.0;

    SchemeDimensionTimeConfig config = {
        .N = N,
        .M = M,
        .K = K,
        .Lx = Lx,
        .Ly = Ly,
        .Lt = Lt,
        .dx = Lx / (N + 1),
        .dy = Ly / (M + 1),
        .dt = Lt / (K + 1)
    };

    QWidget *centralWidget = new QWidget(&window);
    window.setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    centralWidget->setLayout(layout);

    QTabWidget *tabWidget = new QTabWidget(centralWidget);
    layout->addWidget(tabWidget);

    auto trueData = true_calculation(U_xyt, config);
    auto variadicData = variadic_ways(phi1, phi2, phi3, phi4, psi, config);
    auto decimalData = decimal_steps(phi1, phi2, phi3, phi4, psi, config);

    QWidget* trueView = createTensorGraph(trueData, "Analytic function");
    tabWidget->addTab(trueView, "Analytic solution");

    QWidget* variadicView = createTensorGraph(variadicData, "Variadic method");
    tabWidget->addTab(variadicView, "Variadic method");

    QWidget* decimalView = createTensorGraph(decimalData, "Decimal method");
    tabWidget->addTab(decimalView, "Decimal method");

    QWidget* variadicViewErr = createErrorGraph(trueData, variadicData, "Variadic method");
    tabWidget->addTab(variadicViewErr, "Variadic method error");
    
    QWidget* decimalViewErr = createErrorGraph(trueData, decimalData, "Decimal method");
    tabWidget->addTab(decimalViewErr, "Decimal method error");

    window.resize(1024, 768);
    window.show();

    return app.exec();
}