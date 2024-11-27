#include <qdebug.h>
#include <vector>
#include <functional>
#include <QMainWindow>
#include <QtCharts>
#include <QtDataVisualization>
#include <QDebug>

#include "elleptic.h"

#include "../../../SEM6/NM/lab1/Matrix.h"
using namespace numeric;

std::vector<std::vector<double>> startIteration(
    functionD u0y, 
    functionD u1y, 
    functionD uyx0,
    functionD uyxpi,
    Solver<double> solver,
    const SchemeDimensionConfig& config) 
{
    int numNodes = (config.N + 1) * (config.M + 1); 

    Matrix<double> A(numNodes, numNodes);
    std::vector<double> b(numNodes, 0.0);

    const double alpha = 1 / (config.dx * config.dx);
    const double beta = 1 / (config.dy * config.dy);

    auto getInternalIndex = [&](int i, int j) -> int {
        return i * (config.M + 1) + j;
    };

    for (int i = config.N; i >= 0; --i) 
    {
        for (int j = config.M; j >= 0; --j) 
        {
            int idx = getInternalIndex(i, j);
            int idx_left = getInternalIndex(i - 1, j);
            int idx_right = getInternalIndex(i + 1, j);
            int idx_down = getInternalIndex(i, j - 1);
            int idx_up = getInternalIndex(i, j + 1);

            if (i == 0)
            {
                A[idx][idx] = 1;
                b[idx] = u0y(j * config.dy);
            }
            else if (i == config.N)
            {
                A[idx][idx] = 1;
                b[idx] = u1y(j * config.dy);
            }
            else if (j == 0) {

                b[idx] = config.dy * uyx0(i * config.dx);
                A[idx][idx] = -1;
                A[idx][idx_up] = 1;
            }
            else if (j == config.M) 
            {
                b[idx] = config.dy * uyxpi(i * config.dx);
                A[idx][idx] = 1;
                A[idx][idx_down] = -1;
            }
            else
            {
                A[idx][idx] = -2 * (alpha + beta);
                A[idx][idx_left] = alpha;
                A[idx][idx_right] = alpha;
                A[idx][idx_down] = beta;
                A[idx][idx_up] = beta;
            }
        }
    }

    double eps = 1e-7;
    std::vector<double> solution = solver(A, b, eps, 10000);

    std::vector<std::vector<double>> result(config.N + 1, std::vector<double>(config.M + 1));

    for (int i = 0; i <= config.N; ++i) 
    {
        for (int j = 0; j <= config.M; ++j) 
        {
            result[i][j] = solution[i * (config.M + 1) + j];
        }
    }

    return result;
}


std::vector<std::vector<double>> true_calculation(functionDD realFunction, SchemeDimensionConfig &config)
{
    std::vector<std::vector<double>> result(config.N + 1, std::vector<double>(config.M + 1));
    for (int i = 0; i <= config.N; ++i) 
    {
        for (int j = 0; j <= config.M; ++j) 
        {
            result[i][j] = realFunction(i * config.dx, j * config.dy);
        }
    } 

    return result;
}

void printSurfaceDataArray(const QSurfaceDataArray* dataArray) {
    if (!dataArray) {
        qDebug() << "dataArray is null";
        return;
    }

    qDebug() << "Surface Data Array:";
    for (int i = 0; i < dataArray->size(); ++i) {
        const QSurfaceDataRow* row = dataArray->at(i);
        if (!row) {
            qDebug() << "Row" << i << "is null";
            continue;
        }

        QString rowOutput;
        for (int j = 0; j < row->size(); ++j) {
            const  QSurfaceDataItem& point = row->at(j);
            rowOutput += QString("(%1, %2, %3) ")
                             .arg(point.x())
                             .arg(point.y())
                             .arg(point.z());
        }
        qDebug() << "Row" << i << ":" << rowOutput;
    }
}

QWidget* create3DGraph(const std::vector<std::vector<double>>& data) {
    Q3DSurface* surface = new Q3DSurface();
    QSurfaceDataProxy* proxy = new QSurfaceDataProxy();
    QSurface3DSeries* series = new QSurface3DSeries(proxy);

    QSurfaceDataArray* dataArray = new QSurfaceDataArray();

    int rowCount = data.size();
    int columnCount = data[0].size();

    for (int i = 0; i < rowCount; ++i) {
        QSurfaceDataRow* row = new QSurfaceDataRow(columnCount);
        for (int j = 0; j < columnCount; ++j) {
            (*row)[j].setPosition(QVector3D(double(i), data[i][j], double(j)));
        }
        dataArray->append(row);
    }

    proxy->resetArray(dataArray);
    surface->addSeries(series);


    surface->setFlags(surface->flags() ^ Qt::FramelessWindowHint);
    surface->axisX()->setTitle("X-axis");
    surface->axisY()->setTitle("Y-axis (Value)");
    surface->axisZ()->setTitle("Z-axis");
    surface->axisX()->setLabelFormat("%.0f");
    surface->axisY()->setLabelFormat("%.6f");
    surface->axisZ()->setLabelFormat("%.0f");
    series->setBaseColor(Qt::blue);
    QWidget* container = QWidget::createWindowContainer(surface);

    return container;
}

QWidget* createAbsoluteErrorGraph(const std::vector<std::vector<double>>& trueData, const std::vector<std::vector<double>>& iterationData, const QString& methodName) {
    int rowCount = trueData.size();
    int columnCount = trueData[0].size();

    std::vector<std::vector<double>> absErrorData(rowCount, std::vector<double>(columnCount));

    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < columnCount; ++j) {
            absErrorData[i][j] = std::fabs(trueData[i][j] - iterationData[i][j]);
        }
    }

    QSurfaceDataArray* dataArray = new QSurfaceDataArray();
    for (int i = 0; i < rowCount; ++i) {
        QSurfaceDataRow* row = new QSurfaceDataRow(columnCount);
        for (int j = 0; j < columnCount; ++j) {
            (*row)[j].setPosition(QVector3D(double(i), absErrorData[i][j], double(j)));
        }
        dataArray->append(row);
    }

    Q3DSurface* surface = new Q3DSurface();
    QSurfaceDataProxy* proxy = new QSurfaceDataProxy();
    QSurface3DSeries* series = new QSurface3DSeries(proxy);
    proxy->resetArray(dataArray);
    surface->addSeries(series);

    surface->axisX()->setTitle("X-axis");
    surface->axisY()->setTitle("Absolute Error");
    surface->axisZ()->setTitle("Y-axis");
    surface->axisX()->setLabelFormat("%.0f");
    surface->axisY()->setLabelFormat("%.6f");
    surface->axisZ()->setLabelFormat("%.0f");
    series->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);
    series->setFlatShadingEnabled(true);
    series->setBaseColor(Qt::blue);
    surface->setTitle("Absolute Error using " + methodName);

    QWidget* container = QWidget::createWindowContainer(surface);
    return container;
}

QWidget* createL2ErrorGraph(
    const std::vector<std::vector<double>>& trueData,
    functionD u0y, functionD u1y, functionD uyx0, functionD uyxpi,
    Solver<double> solver,
    SchemeDimensionConfig config
) {
    int minNM = 3;
    int maxNM = 25;

    std::vector<std::vector<double>> l2ErrorData(maxNM - minNM + 1, std::vector<double>(maxNM - minNM + 1, 0.0));

    for (int N = minNM; N <= maxNM; ++N) {
        for (int M = minNM; M <= maxNM; ++M) {
            config.N = N;
            config.M = M;
            config.dx = config.Lx / (N + 1);
            config.dy = config.Ly / (M + 1);

            auto iterationData = startIteration(u0y, u1y, uyx0, uyxpi, solver, config);

            double l2Error = 0.0;
            for (int i = 0; i <= N; ++i) {
                for (int j = 0; j <= M; ++j) {
                    double diff = trueData[i][j] - iterationData[i][j];
                    l2Error += diff * diff;
                }
            }
            l2Error = std::sqrt(l2Error);

            l2ErrorData[N - minNM][M - minNM] = l2Error;
        }
    }

    QSurfaceDataArray* dataArray = new QSurfaceDataArray();
    for (int i = 0; i < l2ErrorData.size(); ++i) {
        QSurfaceDataRow* row = new QSurfaceDataRow(l2ErrorData[i].size());
        for (int j = 0; j < l2ErrorData[i].size(); ++j) {
            (*row)[j].setPosition(QVector3D(double(minNM + i), l2ErrorData[i][j], double(minNM + j)));
        }
        dataArray->append(row);
    }

    Q3DSurface* surface = new Q3DSurface();
    QSurfaceDataProxy* proxy = new QSurfaceDataProxy();
    QSurface3DSeries* series = new QSurface3DSeries(proxy);
    proxy->resetArray(dataArray);
    surface->addSeries(series);

    surface->axisX()->setTitle("N (Grid Rows)");
    surface->axisY()->setTitle("L2 Error");
    surface->axisZ()->setTitle("M (Grid Columns)");
    surface->axisX()->setLabelFormat("%.0f");
    surface->axisY()->setLabelFormat("%.6f");
    surface->axisZ()->setLabelFormat("%.0f");

    series->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);
    series->setFlatShadingEnabled(true);
    series->setBaseColor(Qt::blue);

    surface->setTitle("L2 Norm Error vs Grid Size");

    QWidget* container = QWidget::createWindowContainer(surface);
    return container;
}