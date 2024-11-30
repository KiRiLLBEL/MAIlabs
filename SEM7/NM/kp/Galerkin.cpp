#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>
#include <QtCore/QTimer>

#include "Galerkin.hpp"
#include <iostream>
#include <qboxlayout.h>
#include <qvalueaxis.h>
using namespace numeric;

double trapezoidMethod(std::function<double(double)> f, double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));
    for (int i = 1; i < n; i++) {
        sum += f(a + i * h);
    }
    return sum * h;
}

Basis generateBasis(const std::function<double(double)>& startFunc, const GalerkinConfig& config)
{
    Basis basis;
    for(int i = 1; i <= config.N; ++i)
    {
        basis.push_back([startFunc, i](double x){
            return startFunc(x * i);
        });
    }

    return basis;
}

Basis generateBasisDeriv2(const std::function<double(double)>& startFunc, const GalerkinConfig& config)
{
    Basis basis;
    for(int i = 1; i <= config.N; ++i)
    {
        basis.push_back([startFunc, i](double x){
            return -(i * i) * (M_PI * M_PI) * startFunc(x * i);
        });
    }

    return basis;
}

std::vector<double> initialCondition(const std::function<double(double)>& initFunc, const Basis& phi, const GalerkinConfig& config)
{
    Matrix<double> A(config.N, config.N);
    std::vector<double> b(config.N);

    for(int i = 0; i < config.N; ++i)
    {
        for(int j = 0; j < config.N; ++j)
        {

            A[i][j] = trapezoidMethod([&phi, i, j](double x) -> double { return phi[i](x) * phi[j](x);}, config.a, config.b, 1000);
        }
        auto phii = phi[i];
        b[i] = trapezoidMethod([&phii, &initFunc](double x) -> double { return phii(x) * initFunc(x);}, config.a, config.b, 1000);
    }

    double eps = 1e6;
    return iterationSolve(A, b, eps, 10000);
}

std::vector<std::vector<double>> GalerkinSolve(const std::vector<double>& initCoeffs, const Basis& phi, const Basis& dphi2, const GalerkinConfig& config)
{
    std::vector<std::vector<double>> result(config.T + 1, std::vector<double>(config.N));

    result[0] = initCoeffs;
    for(int t = 1; t <= config.T; ++t)
    {
        Matrix<double> M(config.N, config.N + config.N), K(config.N, config.N);
        for(int i = 0; i < config.N; ++i)
        {
            for(int j = 0; j < config.N; ++j)
            {
                M[i][j] = trapezoidMethod([i, j, &phi](double x) -> double { return phi[i](x) * phi[j](x);}, config.a, config.b, 1000);
                K[i][j] = trapezoidMethod([i, j, &dphi2, &phi](double x) -> double { return dphi2[i](x) * phi[j](x);}, config.a, config.b, 1000);
            }
        }
        for(size_t i = 0; i < config.N; ++i) {
            M[i][i + M.rows()] = 1;
        }
        LUMatrix<double> InverseMLU(M);
        auto MInverse = InverseMLU.solve();
        auto MatrixProduct = MInverse * K;
        auto tmp = config.dt * (MatrixProduct * result[t - 1]);
        for(int i = 0; i < config.N; ++i)
        {
            result[t][i] = result[t - 1][i] + tmp[i];
        }
    }

    return result;
}

std::vector<std::vector<double>> true_calculation(
    std::function<double(double, double)> f,
    GalerkinConfig& config)
{
    std::vector<std::vector<double>> results;
    for(int i = 0; i <= config.T; ++i) {
        double t = i * config.dt;
        std::vector<double> f_current(config.L + 1);
        for(int j = 0; j <= config.L; ++j) {
            double x = j * config.dx;
            f_current[j] = f(x, t);
        }
        results.push_back(f_current);
    }
    return results;;
}

std::vector<std::vector<double>> galerkin_calculation(
    std::vector<std::vector<double>> coeffs,
    const Basis& basis,
    GalerkinConfig& config)
{
    std::vector<std::vector<double>> results;
    for(int i = 0; i <= config.T; ++i) {
        std::vector<double> f_current(config.L + 1);
        for(int j = 0; j <= config.L; ++j) {
            double x = j * config.dx;
            double acc = 0;
            for(int a = 0; a < config.N; ++a) {
                acc += coeffs[i][a] * basis[a](x);
            }
            f_current[j] = acc;
        }
        results.push_back(f_current);
    }
    return results;
}

QWidget* create2DGraphWithSlider(const std::vector<std::vector<double>>& data1, const std::vector<std::vector<double>>& data2) {
    int rowCount = data1.size();
    int columnCount = data1[0].size();

    // Создаем два графика для двух наборов данных
    QLineSeries* series1 = new QLineSeries();
    QLineSeries* series2 = new QLineSeries();
    series1->setName("Аналитическое решение");
    series2->setName("Метод Галеркина");

    // Заполняем графики начальными данными для первой строки (или 0-го слоя)
    for (int j = 0; j < columnCount; ++j) {
        series1->append(j, data1[0][j]);  // X = j, Y = data1[0][j]
        series2->append(j, data2[0][j]);  // X = j, Y = data2[0][j]
    }

    // Создаем объекты для графиков
    QChart* chart = new QChart();
    chart->addSeries(series1);
    chart->addSeries(series2);
    chart->setTitle("Methods graphs");

    // Создаем оси
    auto axisX = new QValueAxis;
    axisX->setTitleText("X-axis");
    axisX->setRange(0, columnCount - 1); // Устанавливаем диапазон оси X
    chart->addAxis(axisX, Qt::AlignBottom);
    series1->attachAxis(axisX);
    series2->attachAxis(axisX);

    auto axisY = new QValueAxis;
    axisY->setTitleText("Y-axis");
    axisY->setRange(-2, 2); // Устанавливаем диапазон оси Y (например, от 0 до 1)
    chart->addAxis(axisY, Qt::AlignLeft);
    series1->attachAxis(axisY);
    series2->attachAxis(axisY);

    // Создаем QChartView для отображения графика
    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Создаем слайдер для управления данными
    QSlider* slider = new QSlider(Qt::Horizontal);
    slider->setMinimum(0);
    slider->setMaximum(rowCount - 1);
    slider->setValue(0);

    // Обновляем данные на графиках при изменении значения слайдера
    QObject::connect(slider, &QSlider::valueChanged, [=](int value) {
        series1->clear();
        series2->clear();
        // Обновляем графики для выбранного слоя (строки)
        for (int j = 0; j < columnCount; ++j) {
            series1->append(j, data1[value][j]);
            series2->append(j, data2[value][j]);
        }
    });

    // Создаем вертикальный layout для размещения графика и слайдера
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(chartView);
    layout->addWidget(slider);

    QWidget* container = new QWidget();
    container->setLayout(layout);

    return container;
}
