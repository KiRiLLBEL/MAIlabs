#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QTabWidget>

#include <cmath>
#include "elleptic.h"

auto U_xt = [](double x, double y)
{
    return exp(x) * cos(y);
};

auto u0y = [](double y) 
{
    return cos(y);
};

auto u1y = [](double y)
{
    return M_E * cos(y);
};

auto ux0 = [](double x)
{
    return 0.0;
};

auto uxpi2 = [](double x)
{
    return -exp(x);
};

auto main(int argc, char *argv[]) -> int {
    QApplication app(argc, argv);
    QMainWindow window;

    SchemeDimensionConfig config = {
        .N = 25,
        .M = 25,
        .Ly = M_PI_2,
        .Lx = 1,
        .dy = M_PI_2 / 26.0,
        .dx = 1 / 26.0,
    };

    QWidget *centralWidget = new QWidget(&window);
    window.setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    centralWidget->setLayout(layout);

    QTabWidget *tabWidget = new QTabWidget(centralWidget);
    layout->addWidget(tabWidget);
    
    auto trueData = true_calculation(U_xt, config);
    auto* trueView = create3DGraph(trueData);
    tabWidget->addTab(trueView, "Analytic function view");

    auto iterationData = startIteration(u0y, u1y, ux0, uxpi2, numeric::iterationSolve<double>, config);
    auto* iterationView = create3DGraph(iterationData);
    tabWidget->addTab(iterationView, "Iteration function view");

    auto SeidelData = startIteration(u0y, u1y, ux0, uxpi2, numeric::SeidelSolve<double>, config);
    auto* SeidelView = create3DGraph(SeidelData);
    tabWidget->addTab(SeidelView, "Seidel function view");

    auto UpperRelaxationData = startIteration(u0y, u1y, ux0, uxpi2, numeric::UpperRelaxationSolve<double>, config);
    auto* UpperRelaxationView = create3DGraph(UpperRelaxationData);
    tabWidget->addTab(UpperRelaxationView, "Upper relaxation function view");

    auto* IterationErrView = createAbsoluteErrorGraph(trueData, iterationData, "Simple iteration");
    tabWidget->addTab(IterationErrView, "Simple iteration absolute error");

    auto* SeidelErrView = createAbsoluteErrorGraph(trueData, SeidelData, "Seidel");
    tabWidget->addTab(SeidelErrView, "Seidel absolute error");

    auto* UpperRelaxationErrView = createAbsoluteErrorGraph(trueData, UpperRelaxationData, "Upper relaxation");
    tabWidget->addTab(UpperRelaxationErrView, "Upper relaxation absolute error");

    auto* UpperRelaxationL2View = createL2ErrorGraph(trueData, u0y, u1y, ux0, uxpi2, numeric::UpperRelaxationSolve<double>, config);
    tabWidget->addTab(UpperRelaxationL2View, "Upper relaxation l2 norm err");
    
    window.resize(1024, 768);
    window.show();

    return app.exec();
}