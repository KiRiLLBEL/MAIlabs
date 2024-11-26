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
        .N = 1000,
        .M = 1000,
        .dy = 1 / 1000.0,
        .dx = 1 / 1000.0,
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

    window.resize(1024, 768);
    window.show();

    return app.exec();
}