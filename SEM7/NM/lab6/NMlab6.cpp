#include <cmath>
#include "hyperbolic.h"
#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QTabWidget>

auto U_xt = [](double x, double t, double a = 1){
    return cos(x) * sin(2 * t);
};

auto u_0t = [](double t, double a = 1) {
    return sin(2 * t);
};

auto u_pit = [](double t, double a = 1) {
    return -sin(2 * t);
};

auto u_x0 = [](double x) {
    return 0;
};

auto ut_x0 = [](double x) {
    return 2 * cos(x);
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QMainWindow window;

    QWidget *centralWidget = new QWidget(&window);
    window.setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    centralWidget->setLayout(layout);

    QTabWidget *tabWidget = new QTabWidget(centralWidget);
    layout->addWidget(tabWidget);

    SchemeConfig config {
        .N = 10,
        .K = 100,
        .dx = M_PI / 10,
        .dt = 1.0 / 100
    };
    auto u0 = firstLayer(u_x0, config);
    auto u1 = secondLayer(u_x0, ut_x0, config);
    auto result1 = explicit_scheme(u0, u1, u_0t, u_pit, config);
    auto result2 = implicit_scheme(u0, u1, u_0t, u_pit, config);
    auto true_value = true_calculation(U_xt, config);
    int t = 50;
    QWidget *visualizationWidget = visualize(true_value, result1, result2, config, t);
    tabWidget->addTab(visualizationWidget, "Visualization");
    QWidget *errorOverXWidget = plot_error_over_x(true_value, result1, result2,  config, t);
    tabWidget->addTab(errorOverXWidget, "Error over X");
    int N_min = 10;
    int N_max = 100;
    int N_step = 5;
    int K_min = 100;
    int K_max = 1000;
    int K_step = 5;
    QWidget *error3DExplicit = plot_error_3d_hyperbolic(EXPLICIT, explicit_scheme, U_xt, u_x0, ut_x0, u_0t, u_pit, config, N_min, N_max, N_step, K_min, K_max, K_step);
    tabWidget->addTab(error3DExplicit, "Error 3D Explicit");
    QWidget *error3DImplicit = plot_error_3d_hyperbolic(IMPLICIT, implicit_scheme, U_xt, u_x0, ut_x0, u_0t, u_pit, config, N_min, N_max, N_step, K_min, K_max, K_step);
    tabWidget->addTab(error3DImplicit, "Error 3D Implicit");

    window.resize(1024, 768);
    window.show();

    return app.exec();
}