#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QTabWidget>

#include <cmath>
#include "parabolic.h"

auto U_xt = [](double x, double t, double a = 1){
    return exp(-a * t) * cos(x);
};

auto u_0t = [](double t, double a = 1) {
    return exp(-a * t);
};

auto u_pit = [](double t, double a = 1) {
    return -exp(-a * t);
};

auto u_x0 = [](double x) {
    return cos(x);
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
    auto u0 = start(u_x0, config);
    auto result1 = explicit_scheme(u0, u_0t, u_pit, config);
    auto result2 = implicit_scheme(u0, u_0t, u_pit, config);
    auto result3 = krank_nikolson_scheme(u0, u_0t, u_pit, config);
    auto true_value = true_calculation(U_xt, config);
    int t = 50;
    QWidget *visualizationWidget = visualize(true_value, result1, result2, result3, config, t);
    tabWidget->addTab(visualizationWidget, "Visualization");
    QWidget *errorOverXWidget = plot_error_over_x(true_value, result1, result2, result3, config, t);
    tabWidget->addTab(errorOverXWidget, "Error over X");

    int N_min = 1;
    int N_max = 200;
    int N_step = 1;
    int K_min = 1;
    int K_max = 200;
    int K_step = 1;
    QWidget *error3DExplicit = plot_error_3d(EXPLICIT, explicit_scheme, U_xt, u_x0, u_0t, u_pit, config, N_min, N_max, N_step, K_min, K_max, K_step);
    tabWidget->addTab(error3DExplicit, "Error 3D Explicit");
    QWidget *error3DImplicit = plot_error_3d(IMPLICIT, implicit_scheme, U_xt, u_x0, u_0t, u_pit, config, N_min, N_max, N_step, K_min, K_max, K_step);
    tabWidget->addTab(error3DImplicit, "Error 3D Implicit");
    QWidget *error3DKrankNikolson = plot_error_3d(KRANK_NIKOLSON, krank_nikolson_scheme, U_xt, u_x0, u_0t, u_pit, config, N_min, N_max, N_step, K_min, K_max, K_step);
    tabWidget->addTab(error3DKrankNikolson, "Error 3D Crank-Nicolson");

    window.resize(1024, 768);
    window.show();

    return app.exec();
}