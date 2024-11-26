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
    const SchemeDimensionConfig& config) 
{
    int matrixSize = (config.N + 1) * (config.M + 1);

    Matrix<double> A(matrixSize, matrixSize);

    const double alpha = 1.0 / (config.dx * config.dx);
    const double beta = 1.0 / (config.dy * config.dy);

    std::vector<double> b((config.N + 1) * (config.M + 1), 0.0);
    for (int i = 0; i <= config.N; ++i) 
    {
        for (int j = 0; j <= config.M; ++j) 
        {
            int idx = i * (config.M + 1) + j;
            if (i == 0) {
                b[idx] = u0y(j * config.dy);
            } else if (i == config.N) {
                b[idx] = u1y(j * config.dy);
            } else if (j == 0) {
                int idx1 = i * (config.M + 1) + (j + 1);
                b[idx] = config.dy * uyx0(i * config.dx);
                A[idx][idx] = 0;
                A[idx][idx1] = -1.0;
            } else if (j == config.M) {
                int idx1 = i * (config.M + 1) + (j - 1);
                b[idx] = config.dy * uyxpi(i * config.dx);
                A[idx][idx] = 0;
                A[idx][idx1] = -1.0;
            } else {
                int idx_left = (i - 1) * (config.M + 1) + j;
                int idx_right = (i + 1) * (config.M + 1) + j;
                int idx_down = i * (config.M + 1) + (j - 1);
                int idx_up = i * (config.M + 1) + (j + 1);

                A[idx][idx_left] = -alpha;
                A[idx][idx_right] = -alpha;
                A[idx][idx_down] = -beta;
                A[idx][idx_up] = -beta;
                A[idx][idx] = 2 * (alpha + beta);
            }
        }
    }

    double eps = 1e-6;
    std::vector<std::vector<double>> result(config.N + 1, std::vector<double>(config.M + 1));
    std::vector<double> solution = iterationSolve(A, b, eps);
    for (int i = 0; i <= config.N; ++i) 
    {
        for (int j = 0; j <= config.M; ++j) 
        {
            int idx = i * (config.M + 1) + j;
            result[i][j] = solution[idx];
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

    QWidget* container = QWidget::createWindowContainer(surface);
    // surface->setFlags(surface->flags() | Qt::MSWindowsOwnDC);
    surface->axisX()->setTitle("X-axis");
    surface->axisY()->setTitle("Y-axis (Value)");
    surface->axisZ()->setTitle("Z-axis");

    // printSurfaceDataArray(dataArray);

    return container;
}