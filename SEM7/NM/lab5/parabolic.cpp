#include "parabolic.h"
#include <vector>
#include <functional>
#include <QMainWindow>
#include <QtCharts>
#include <QtDataVisualization>

#include "../../../SEM6/NM/lab1/Matrix.h"
using namespace numeric;

std::vector<double> start(std::function<double(double)> start_x, SchemeConfig& config) {
    std::vector<double> start_pos(config.N);
    for(int i = 0; i < config.N; ++i) {
        double x = i * config.dx;
        start_pos[i] = start_x(x);
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
    std::vector<double>& start,
    std::function<double(double, double)> guard_start, 
    std::function<double(double, double)> guard_end, 
    SchemeConfig& config) {

    std::vector<std::vector<double>> results;
    std::vector<double> current = start;
    std::vector<double> next(config.N);
    for(int i = 0; i < config.K; ++i) {
        double t = i * config.dt;
        next[0] = guard_start(t, config.a);
        next[config.N - 1] = guard_end(t, config.a);

        for(int j = 1; j < config.N - 1; ++j) {
            next[j] = current[j] + config.a * config.dt * (current[j + 1] - 2 * current[j] + current[j - 1]) / (config.dx * config.dx);
        }
        current = next;
        results.push_back(current);
    }
    return results;
}

std::vector<std::vector<double>> implicit_scheme(
    std::vector<double>& start, 
    std::function<double(double, double)> guard_start, 
    std::function<double(double, double)> guard_end, 
    SchemeConfig& config) {
    std::vector<std::vector<double>> results;
    std::vector<double> u = start;
    std::vector<double> u_new(config.N);

    Matrix<double> matrix(config.N, config.N);
    std::vector<double> d(config.N);

    double sigma = (config.a * config.dt) / (config.dx * config.dx);
    double A = sigma;
    double B = -(1 + 2 * sigma);
    double C = sigma;

    for (int i = 0; i < config.K; ++i) {
        double t = (i + 1) * config.dt;
        for (size_t j = 0; j < config.N; ++j) {
            if (j == 0) {
                matrix[j][j] = B;
                matrix[j][j + 1] = C;
                d[j] = -(u[j] + sigma * guard_start(t, config.a));
            } else if (j == config.N - 1) {
                matrix[j][j - 1] = A;
                matrix[j][j] = B;
                d[j] = -(u[j] + sigma * guard_end(t, config.a));
            } else {
                d[j] = -u[j];
                matrix[j][j - 1] = A;
                matrix[j][j] = B;
                matrix[j][j + 1] = C;
            }
        }

        // Решаем систему уравнений
        u_new = tridiagonalSolve(matrix, d);

        u = u_new;
        results.push_back(u);
    }
    return results;
}

std::vector<std::vector<double>> krank_nikolson_scheme(
    std::vector<double>& start, 
    std::function<double(double, double)> guard_start, 
    std::function<double(double, double)> guard_end, 
    SchemeConfig& config) {
    std::vector<std::vector<double>> results;
    std::vector<double> u = start;
    std::vector<double> u_new(config.N);

    Matrix<double> matrix(config.N, config.N);
    std::vector<double> d(config.N);

    double sigma = (config.a * config.dt) / (config.dx * config.dx) / 2;
    double A = sigma;
    double B = -(1 + 2 * sigma);
    double C = sigma;

    for (int i = 0; i < config.K; ++i) {
        double t_k1 = (i + 1) * config.dt;
        double t = i * config.dt;
        for (size_t j = 0; j < config.N; ++j) {
            if (j == 0) {
                matrix[j][j] = B;
                matrix[j][j + 1] = C;
                d[j] = (-sigma * guard_start(t, config.a) + (2 * sigma - 1) * u[j] - sigma * u[j + 1] - sigma * guard_start(t_k1, config.a)); 
            } else if (j == config.N - 1) {
                matrix[j][j - 1] = A;
                matrix[j][j] = B;
                d[j] = (-sigma * u[j - 1] + (2 * sigma - 1) * u[j] - sigma * guard_end(t, config.a) - sigma * guard_end(t_k1, config.a)); 
            } else {
                d[j] = (-sigma * u[j - 1] + (2 * sigma - 1) * u[j] - sigma * u[j + 1]);
                matrix[j][j - 1] = A;
                matrix[j][j] = B;
                matrix[j][j + 1] = C;
            }
        }

        // Решаем систему уравнений
        u_new = tridiagonalSolve(matrix, d);

        u = u_new;
        results.push_back(u);
    }
    return results;
}

QWidget* visualize(
    const std::vector<std::vector<double>>& true_value,
    const std::vector<std::vector<double>>& data1,
    const std::vector<std::vector<double>>& data2,
    const std::vector<std::vector<double>>& data3,
    SchemeConfig& config, int time) {

    QLineSeries *series1 = new QLineSeries();
    QLineSeries *series2 = new QLineSeries();
    QLineSeries *series3 = new QLineSeries();
    QLineSeries *seriesTrue = new QLineSeries();

    for (int i = 0; i < config.N; ++i) {
        double x = i * config.dx;
        series1->append(x, data1[time][i]);
        series2->append(x, data2[time][i]);
        series3->append(x, data3[time][i]);
        seriesTrue->append(x, true_value[time][i]);
    }

    series1->setName("Явная схема");
    series2->setName("Неявная схема");
    series3->setName("Схема Кранка–Николсона");
    seriesTrue->setName("Аналитическое решение");

    // Настраиваем цвета серий
    series1->setColor(Qt::red);
    series2->setColor(Qt::green);
    series3->setColor(Qt::blue);
    seriesTrue->setColor(Qt::black);

    QChart *chart = new QChart();
    chart->addSeries(series1);
    chart->addSeries(series2);
    chart->addSeries(series3);
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
    const std::vector<std::vector<double>>& data3,
    SchemeConfig& config, int time) {

    QLineSeries *series1 = new QLineSeries();
    QLineSeries *series2 = new QLineSeries();
    QLineSeries *series3 = new QLineSeries();

    for (int i = 0; i < config.N; ++i) {
        double x = i * config.dx;
        double error1 = std::abs(true_value[time][i] - data1[time][i]);
        double error2 = std::abs(true_value[time][i] - data2[time][i]);
        double error3 = std::abs(true_value[time][i] - data3[time][i]);

        series1->append(x, error1);
        series2->append(x, error2);
        series3->append(x, error3);
    }

    series1->setName("Погрешность явной схемы");
    series2->setName("Погрешность неявной схемы");
    series3->setName("Погрешность схемы Кранка–Николсона");

    series1->setColor(Qt::red);
    series2->setColor(Qt::green);
    series3->setColor(Qt::blue);

    QChart *chart = new QChart();
    chart->addSeries(series1);
    chart->addSeries(series2);
    chart->addSeries(series3);

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


QWidget* plot_error_3d(
    SchemeType type,
    const std::function<std::vector<std::vector<double>>(std::vector<double>&, std::function<double(double, double)>, std::function<double(double, double)>, SchemeConfig&)>& scheme_function,
    const std::function<double(double, double, double)>& analytical_solution,
    std::function<double(double)> initial_condition,
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

            if (type == EXPLICIT) {
                double alpha = (config.a * config.dt) / (config.dx * config.dx);
                if (alpha > 0.5) {
                    error_row.append(0.0);
                    continue;
                }
            }

            auto u0 = start(initial_condition, config);
            auto true_value = true_calculation(analytical_solution, config);
            auto result = scheme_function(u0, guard_start, guard_end, config);

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
