#include "variable.h"
#include <vector>
#include <QMainWindow>
#include <QtCharts>
#include <QtDataVisualization>
#include <QSlider>

#include "../../../SEM6/NM/lab1/Matrix.h"

using namespace numeric;

Tensor true_calculation(FunctionDDD realFunction, SchemeDimensionTimeConfig& config)
{
    Tensor res(config.K + 1, std::vector<std::vector<double>>(config.N + 1, std::vector<double>(config.M + 1)));

    for (int k = 0; k <= config.K; ++k)
    {
        for (int i = 0; i <= config.N; ++i)
        {
            for (int j = 0; j <= config.M; ++j)
            {
                res[k][i][j] = realFunction(i * config.dx, j * config.dy, k * config.dt);
            }
        }
    }
    return res;
}

Tensor variadic_ways(
    FunctionDD phi1,
    FunctionDD phi2,
    FunctionDD phi3,
    FunctionDD phi4,
    FunctionDD psi,
    SchemeDimensionTimeConfig& config) {
    Tensor result(config.K + 1, std::vector<std::vector<double>>(config.N + 1, std::vector<double>(config.M + 1)));
    for (int i = 0; i <= config.N; ++i)
    {
        for(int j = 0; j <= config.M; ++j)
        {
            result[0][i][j] = psi(i * config.dx, j * config.dy);
        }
    }

    for (int k = 1; k <= config.K; ++k)
    {
        std::vector<std::vector<double>> halfStep(config.N + 1, std::vector<double>(config.M + 1));
        double haltTime = config.dt * k - (config.dt / 2);
        for(int i = 0; i <= config.N; ++i)
        {
            result[k][i][0] = phi3(i * config.dx, k * config.dt);
            result[k][i][config.M] = phi4(i * config.dx, k * config.dt);

            halfStep[i][0] = phi3(i * config.dx, haltTime);
            halfStep[i][config.M] = phi4(i * config.dx, haltTime);
        }

        for(int j = 0; j <= config.M; ++j)
        {
            result[k][0][j] = phi1(j * config.dy, k * config.dt);
            result[k][config.N][j] = phi2(j * config.dy, k * config.dt);

            halfStep[0][j] = phi1(j * config.dy, haltTime);
            halfStep[config.N][j] = phi2(j * config.dy, haltTime);
        }

        for (int j = 1; j < config.M; ++j)
        {
            Matrix<double> A(config.N - 1, config.N - 1);
            std::vector<double> b(config.N - 1);

            double alpha = 1 / (config.dx * config.dx);
            double beta = -2 * (1 / (config.dx * config.dx) + 1 / config.dt);

            double gamma = -1 / (config.dy * config.dy);
            double delta = 2 * (1 / (config.dy * config.dy) - 1 / config.dt);

            A[0][0] = beta;
            A[0][1] = alpha;
            A[config.N - 2][config.N - 2] = beta;
            A[config.N - 2][config.N - 3] = alpha;

            for (int i = 1; i < config.N - 2; ++i)
            {
                A[i][i] = beta;
                A[i][i - 1] = alpha;
                A[i][i + 1] = alpha;
            }

            for (int i = 1; i <= config.N - 1; ++i)
            {
                b[i - 1] = result[k - 1][i][j - 1] * gamma + result[k - 1][i][j] * delta + result[k - 1][i][j + 1] * gamma;
            }

            b[0] -= alpha * phi1(j * config.dy, haltTime);
            b[config.N - 2] -= alpha * phi2(j * config.dy, haltTime);
            auto solution = tridiagonalSolve(A, b);
            for(int i = 1; i < config.N; ++i)
            {
                halfStep[i][j] = solution[i - 1];
            }
        }

        for (int i = 1; i < config.N; ++i)
        {
            Matrix<double> A(config.M - 1, config.M - 1);
            std::vector<double> b(config.M - 1);

            double alpha = 1 / (config.dy * config.dy);
            double beta = -2 * (1 / (config.dy * config.dy) + 1 / config.dt);

            double gamma = -1 / (config.dx * config.dx);
            double delta = 2 * (1 / (config.dx * config.dx) - 1 / config.dt);

            A[0][0] = beta;
            A[0][1] = alpha;
            A[config.M - 2][config.M - 2] = beta;
            A[config.M - 2][config.M - 3] = alpha;

            for (int j = 1; j < config.M - 2; ++j)
            {
                A[j][j] = beta;
                A[j][j - 1] = alpha;
                A[j][j + 1] = alpha;
            }
            
            for (int j = 1; j <= config.M - 1; ++j)
            {
                b[j - 1] = halfStep[i - 1][j] * gamma + halfStep[i][j] * delta + halfStep[i + 1][j] * gamma;
            }

            b[0] -= alpha * phi3(i * config.dx, k * config.dt);
            b[config.M - 2] -= alpha * phi4(i * config.dx, k * config.dt);
            auto solution = tridiagonalSolve(A, b);
            for(int j = 1; j < config.M; ++j)
            {
                result[k][i][j] = solution[j - 1];
            }
        }
    }

    return result;
}

Tensor decimal_steps(
    FunctionDD phi1,
    FunctionDD phi2,
    FunctionDD phi3,
    FunctionDD phi4,
    FunctionDD psi,
    SchemeDimensionTimeConfig& config) {
    Tensor result(config.K + 1, std::vector<std::vector<double>>(config.N + 1, std::vector<double>(config.M + 1)));
    for (int i = 0; i <= config.N; ++i)
    {
        for(int j = 0; j <= config.M; ++j)
        {
            result[0][i][j] = psi(i * config.dx, j * config.dy);
        }
    }

    for (int k = 1; k <= config.K; ++k)
    {
        std::vector<std::vector<double>> halfStep(config.N + 1, std::vector<double>(config.M + 1));
        double haltTime = config.dt * k - (config.dt / 2);
        for(int i = 0; i <= config.N; ++i)
        {
            result[k][i][0] = phi3(i * config.dx, k * config.dt);
            result[k][i][config.M] = phi4(i * config.dx, k * config.dt);

            halfStep[i][0] = phi3(i * config.dx, haltTime);
            halfStep[i][config.M] = phi4(i * config.dx, haltTime);
        }

        for(int j = 0; j <= config.M; ++j)
        {
            result[k][0][j] = phi1(j * config.dy, k * config.dt);
            result[k][config.N][j] = phi2(j * config.dy, k * config.dt);

            halfStep[0][j] = phi1(j * config.dy, haltTime);
            halfStep[config.N][j] = phi2(j * config.dy, haltTime);
        }

        for (int j = 1; j < config.M; ++j)
        {
            Matrix<double> A(config.N - 1, config.N - 1);
            std::vector<double> b(config.N - 1);

            double alpha = 1 / (config.dx * config.dx);
            double beta = -2 / (config.dx * config.dx) - 1 / config.dt;

            double delta = -1 / config.dt;

            A[0][0] = beta;
            A[0][1] = alpha;
            A[config.N - 2][config.N - 2] = beta;
            A[config.N - 2][config.N - 3] = alpha;

            for (int i = 1; i < config.N - 2; ++i)
            {
                A[i][i] = beta;
                A[i][i - 1] = alpha;
                A[i][i + 1] = alpha;
            }

            for (int i = 1; i <= config.N - 1; ++i)
            {
                b[i - 1] = result[k - 1][i][j] * delta;
            }

            b[0] -= alpha * phi1(j * config.dy, haltTime);
            b[config.N - 2] -= alpha * phi2(j * config.dy, haltTime);
            auto solution = tridiagonalSolve(A, b);
            for(int i = 1; i < config.N; ++i)
            {
                halfStep[i][j] = solution[i - 1];
            }
        }

        for (int i = 1; i < config.N; ++i)
        {
            Matrix<double> A(config.M - 1, config.M - 1);
            std::vector<double> b(config.M - 1);

            double alpha = 1 / (config.dy * config.dy);
            double beta = -2 / (config.dy * config.dy) - 1 / config.dt;

            double delta = -1 / config.dt;;

            A[0][0] = beta;
            A[0][1] = alpha;
            A[config.M - 2][config.M - 2] = beta;
            A[config.M - 2][config.M - 3] = alpha;

            for (int j = 1; j < config.M - 2; ++j)
            {
                A[j][j] = beta;
                A[j][j - 1] = alpha;
                A[j][j + 1] = alpha;
            }
            
            for (int j = 1; j <= config.M - 1; ++j)
            {
                b[j - 1] = halfStep[i][j] * delta;
            }

            b[0] -= alpha * phi3(i * config.dx, k * config.dt);
            b[config.M - 2] -= alpha * phi4(i * config.dx, k * config.dt);
            auto solution = tridiagonalSolve(A, b);
            for(int j = 1; j < config.M; ++j)
            {
                result[k][i][j] = solution[j - 1];
            }
        }
    }

    return result;
}

QWidget* createTensorGraph(const std::vector<std::vector<std::vector<double>>>& tensorData, const QString& methodName) {
    int kCount = tensorData.size();
    int iCount = tensorData[0].size();
    int jCount = tensorData[0][0].size();

    QSurfaceDataArray* dataArray = new QSurfaceDataArray();
    for (int i = 0; i < iCount; ++i) {
        QSurfaceDataRow* row = new QSurfaceDataRow(jCount);
        for (int j = 0; j < jCount; ++j) {
            (*row)[j].setPosition(QVector3D(double(i), double(tensorData[0][i][j]), double(j)));
        }
        dataArray->append(row);
    }

    Q3DSurface* surface = new Q3DSurface();
    QSurfaceDataProxy* proxy = new QSurfaceDataProxy();
    QSurface3DSeries* series = new QSurface3DSeries(proxy);
    proxy->resetArray(dataArray);
    surface->addSeries(series);

    surface->axisX()->setTitle("X-axis");
    surface->axisY()->setTitle("Z-axis");
    surface->axisZ()->setTitle("Y-axis");
    surface->axisX()->setLabelFormat("%.0f");
    surface->axisY()->setLabelFormat("%.6f");
    surface->axisZ()->setLabelFormat("%.0f");
    surface->axisY()->setRange(0, 1);
    series->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);
    series->setFlatShadingEnabled(true);
    series->setBaseColor(Qt::blue);
    surface->setTitle("Tensor Data Visualization (" + methodName + ")");

    QSlider* slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, kCount - 1);
    slider->setValue(0);
    slider->setTickInterval(1);
    slider->setTickPosition(QSlider::TicksBelow);
    QObject::connect(slider, &QSlider::valueChanged, [=](int value) {
        for (int i = 0; i < iCount; ++i) {
            for (int j = 0; j < jCount; ++j) {
                (*dataArray)[i]->replace(j, QVector3D(double(i), double(tensorData[value][i][j]), double(j)));
            }
        }
        proxy->resetArray(dataArray);
    });

    QWidget* container = QWidget::createWindowContainer(surface);
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(container);
    layout->addWidget(slider);

    QWidget* mainWidget = new QWidget();
    mainWidget->setLayout(layout);

    return mainWidget;
}

QWidget* createErrorGraph(
    const Tensor& trueValue, 
    const Tensor& dataValue, 
    const QString& methodName) {
    int kCount = trueValue.size();
    int iCount = trueValue[0].size();
    int jCount = trueValue[0][0].size();

    QSurfaceDataArray* errorArray = new QSurfaceDataArray();
    for (int i = 0; i < iCount; ++i) {
        QSurfaceDataRow* row = new QSurfaceDataRow(jCount);
        for (int j = 0; j < jCount; ++j) {
            double error = std::abs(trueValue[0][i][j] - dataValue[0][i][j]);
            (*row)[j].setPosition(QVector3D(double(i), error, double(j)));
        }
        errorArray->append(row);
    }

    Q3DSurface* surface = new Q3DSurface();
    QSurfaceDataProxy* proxy = new QSurfaceDataProxy();
    QSurface3DSeries* series = new QSurface3DSeries(proxy);
    proxy->resetArray(errorArray);
    surface->addSeries(series);

    surface->axisX()->setTitle("X-axis");
    surface->axisY()->setTitle("Error");
    surface->axisZ()->setTitle("Y-axis");
    surface->axisX()->setLabelFormat("%.0f");
    surface->axisY()->setLabelFormat("%.6f");
    surface->axisZ()->setLabelFormat("%.0f");
    surface->axisY()->setRange(0, 0.01);
    series->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);
    series->setFlatShadingEnabled(true);
    series->setBaseColor(Qt::red);
    surface->setTitle("Absolute Error Visualization (" + methodName + ")");
    QSlider* slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, kCount - 1);
    slider->setValue(0);
    slider->setTickInterval(1);
    slider->setTickPosition(QSlider::TicksBelow);
    QObject::connect(slider, &QSlider::valueChanged, [=](int value) {
        for (int i = 0; i < iCount; ++i) {
            for (int j = 0; j < jCount; ++j) {
                double error = std::abs(trueValue[value][i][j] - dataValue[value][i][j]);
                (*errorArray)[i]->replace(j, QVector3D(double(i), error, double(j)));
            }
        }
        proxy->resetArray(errorArray);
    });

    QWidget* container = QWidget::createWindowContainer(surface);
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(container);
    layout->addWidget(slider);

    QWidget* mainWidget = new QWidget();
    mainWidget->setLayout(layout);

    return mainWidget;
}
