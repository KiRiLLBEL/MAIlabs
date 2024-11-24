#include "hyperbolic.h"
#include <vector>
#include <functional>
#include <QMainWindow>
#include <QtCharts>
#include <QtDataVisualization>
#include "../../../SEM6/NM/lab1/Matrix.h"
using namespace numeric;

std::vector<double> firstLayer(std::function<double(double)> start_x, SchemeConfig& config) {
    std::vector<double> start_pos(config.N);
    for(int i = 0; i < config.N; ++i) {
        double x = i * config.dx;
        start_pos[i] = start_x(x);
    }
    return start_pos;
}

std::vector<double> secondLayer(
    std::function<double(double)> psi1, 
    std::function<double(double)> psi2, 
    SchemeConfig& config) {
    std::vector<double> start_pos(config.N);
    for(int i = 0; i < config.N; ++i) {
        double x = i * config.dx;
        start_pos[i] = psi1(x) + psi2(x) * config.dt;
    }
    return start_pos;
}

std::vector<std::vector<double>> true_calculation(
    std::function<double(double, double, double)> f,
    SchemeConfig& config) {
    std::vector<std::vector<double>> results;
    for(int i = 0; i < config.K; ++i) {
        double t = i * config.dt;
        std::vector<double> f_current(config.N);
        for(int j = 0; j < config.N; ++j) {
            double x = j * config.dx;
            f_current[j] = f(x, t, config.a);
        }
        results.push_back(f_current);
    }
    return results;;
}

std::vector<std::vector<double>> explicit_scheme(
    std::vector<double>& start1,
    std::vector<double>& start2,
    std::function<double(double, double)> guard_start, 
    std::function<double(double, double)> guard_end, 
    SchemeConfig& config) {
    auto sigma = config.a * config.a * config.dt * config.dt / (config.dx * config.dx);
    

    std::vector<std::vector<double>> results;
    std::vector<double> prev = start1;
    std::vector<double> current = start2;
    std::vector<double> next(config.N);
    results.push_back(prev);
    results.push_back(current);
    for(int i = 0; i < config.K; ++i) {
        double t = i * config.dt;
        next[0] = guard_start(t + config.dt + config.dt, config.a);
        next[config.N - 1] = guard_end(t + config.dt + config.dt, config.a);

        for(int j = 1; j < config.N - 1; ++j) {
            next[j] = 
                current[j + 1] * sigma + 
                current[j] * (-2 * sigma + 2 - 3 * config.dt * config.dt) + 
                current[j - 1] * sigma -
                prev[j];
        }
        prev = current;
        current = next;
        results.push_back(current);
    }
    return results;
}

std::vector<std::vector<double>> implicit_scheme(
    std::vector<double>& start1,
    std::vector<double>& start2,
    std::function<double(double, double)> guard_start, 
    std::function<double(double, double)> guard_end, 
    SchemeConfig& config) {
    std::vector<std::vector<double>> results;
    std::vector<double> u_prev = start1;
    std::vector<double> u_cur = start2;
    std::vector<double> u_new(config.N);
    results.push_back(u_prev);
    results.push_back(u_cur);

    Matrix<double> matrix(config.N, config.N);
    std::vector<double> d(config.N);

    double A = -config.a * config.dt * config.dt / config.dx / config.dx;
    double B = 1 + 2 * config.a * config.dt * config.dt / config.dx / config.dx + 3 * config.dt * config.dt;
    double C = -config.a * config.dt * config.dt / config.dx / config.dx;

    for (int i = 0; i < config.K; ++i) {
        double t = (i + 2) * config.dt;
        for (size_t j = 0; j < config.N; ++j) {
            if (j == 0) {
                matrix[j][j] = 1 + 2 * config.a * config.dt * config.dt / config.dx / config.dx + 3 * config.dt * config.dt;
                matrix[j][j + 1] = -config.a * config.dt * config.dt / config.dx / config.dx;
                d[j] = guard_start(t, config.a);
            } else if (j == config.N - 1) {
                matrix[j][j - 1] =  -config.a * config.dt * config.dt / config.dx / config.dx;
                matrix[j][j] = 1 + 2 * config.a * config.dt * config.dt / config.dx / config.dx + 3 * config.dt * config.dt;
                d[j] = guard_end(t, config.a);
            } else {
                d[j] = 2 * u_cur[j] - u_prev[j];
                matrix[j][j - 1] = A;
                matrix[j][j] = B;
                matrix[j][j + 1] = C;
            }
        }

        u_new = tridiagonalSolve(matrix, d);
        u_prev = u_cur;
        u_cur = u_new;
        results.push_back(u_cur);
    }
    return results;
}

QWidget* visualize(
    const std::vector<std::vector<double>>& true_value, 
    const std::vector<std::vector<double>>& data1, 
    const std::vector<std::vector<double>>& data2,
    SchemeConfig& config, int time) {

    QLineSeries *series1 = new QLineSeries();
    QLineSeries *series2 = new QLineSeries();
    QLineSeries *seriesTrue = new QLineSeries();

    for (int i = 0; i < config.N; ++i) {
        double x = i * config.dx;
        series1->append(x, data1[time][i]);
        series2->append(x, data2[time][i]);
        seriesTrue->append(x, true_value[time][i]);
    }

    series1->setName("Явная схема");
    series2->setName("Неявная схема");
    seriesTrue->setName("Аналитическое решение");

    series1->setColor(Qt::red);
    series2->setColor(Qt::green);
    seriesTrue->setColor(Qt::black);

    QChart *chart = new QChart();
    chart->addSeries(series1);
    chart->addSeries(series2);
    chart->addSeries(seriesTrue);

    chart->setTitle("Схема в момент времени t = " + QString::number(time * config.dt));
    chart->createDefaultAxes();

    chart->axes(Qt::Horizontal).first()->setTitleText("x");
    chart->axes(Qt::Vertical).first()->setTitleText("U");

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    return chartView;
}

QWidget* plot_error_over_x(
    const std::vector<std::vector<double>>& true_value,
    const std::vector<std::vector<double>>& data1,
    const std::vector<std::vector<double>>& data2,
    SchemeConfig& config, int time) {
    QLineSeries *series1 = new QLineSeries();
    QLineSeries *series2 = new QLineSeries();

    for (int i = 0; i < config.N; ++i) {
        double x = i * config.dx;
        double error1 = std::abs(true_value[time][i] - data1[time][i]);
        double error2 = std::abs(true_value[time][i] - data2[time][i]);

        series1->append(x, error1);
        series2->append(x, error2);
    }

    series1->setName("Погрешность явной схемы");
    series2->setName("Погрешность неявной схемы");

    series1->setColor(Qt::red);
    series2->setColor(Qt::green);

    QChart *chart = new QChart();
    chart->addSeries(series1);
    chart->addSeries(series2);

    chart->setTitle("Погрешность в момент времени t = " + QString::number(time * config.dt));
    chart->createDefaultAxes();

    chart->axes(Qt::Horizontal).first()->setTitleText("x");
    chart->axes(Qt::Vertical).first()->setTitleText("Погрешность");

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    return chartView;
}

QWidget* plot_error_3d_hyperbolic(
    SchemeType type,
    const std::function<std::vector<std::vector<double>>(std::vector<double>&, std::vector<double>&, std::function<double(double, double)>, std::function<double(double, double)>, SchemeConfig&)>& scheme_function,
    const std::function<double(double, double, double)>& analytical_solution,
    std::function<double(double)> initial_condition,
    std::function<double(double)> initial_velocity,
    std::function<double(double, double)> guard_start,
    std::function<double(double, double)> guard_end,
    SchemeConfig& config,
    int N_min, int N_max, int N_step,
    int K_min, int K_max, int K_step) {

    QVector<double> N_values;
    QVector<double> K_values;
    QVector<QVector<double>> error_matrix;

    for (int N = N_min; N <= N_max; N += N_step) {
        N_values.append(N);
    }
    for (int K = K_min; K <= K_max; K += K_step) {
        K_values.append(K);
    }

    for (int K_idx = 0; K_idx < K_values.size(); ++K_idx) {
        QVector<double> error_row;
        int K = K_values[K_idx];

        for (int N_idx = 0; N_idx < N_values.size(); ++N_idx) {
            int N = N_values[N_idx];

            config.N = N;
            config.dx = M_PI / (N - 1);
            config.K = K;
            config.dt = 1.0 / K;

            double alpha = (config.a * config.dt * config.dt) / config.dx * config.dx;
            if (alpha > 1.0) {
                error_row.append(0.0);
                continue;
            }

            auto u0 = firstLayer(initial_condition, config);
            auto v0 = secondLayer(initial_condition, initial_velocity, config);

            auto true_value = true_calculation(analytical_solution, config);

            auto result = scheme_function(u0, v0, guard_start, guard_end, config);

            double total_error = 0.0;
            int total_points = config.K * config.N;

            for (int k = 0; k < config.K; ++k) {
                for (int i = 0; i < config.N; ++i) {
                    total_error += std::abs(true_value[k][i] - result[k][i]);
                }
            }

            double avg_error = total_error / total_points;
            error_row.append(avg_error);
        }
        error_matrix.append(error_row);
    }


    Q3DSurface *graph = new Q3DSurface();

    QWidget *container = QWidget::createWindowContainer(graph);

    QSurfaceDataArray *dataArray = new QSurfaceDataArray();

    double scaleFactor = double(K_max) / N_max;

    for (int i = 0; i < N_values.size(); ++i) {
        QSurfaceDataRow *dataRow = new QSurfaceDataRow(K_values.size());
        for (int j = 0; j < K_values.size(); ++j) {
            double N = N_values[i];
            double K = K_values[j];
            double error = error_matrix[j][i];

            (*dataRow)[j].setPosition(QVector3D(N, error, K / scaleFactor));
        }
        *dataArray << dataRow;
    }

    QSurface3DSeries *series = new QSurface3DSeries();
    series->dataProxy()->resetArray(dataArray);

    graph->addSeries(series);
    graph->axisX()->setTitle("N");
    graph->axisX()->setTitleVisible(true);
    graph->axisY()->setTitle("Ошибка");
    graph->axisY()->setTitleVisible(true);
    graph->axisZ()->setTitle("K");
    graph->axisZ()->setTitleVisible(true);

    graph->activeTheme()->setType(Q3DTheme::ThemeQt);
    graph->setShadowQuality(QAbstract3DGraph::ShadowQualitySoftLow);
    graph->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPresetFront);

    graph->axisX()->setRange(N_min, N_max);
    graph->axisY()->setAutoAdjustRange(true);
    graph->axisZ()->setRange(K_min / scaleFactor, K_max / scaleFactor);
    return container;
}
