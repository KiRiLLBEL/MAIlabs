#include <iostream>
#include "Matrix.h"
using namespace std;
using namespace numeric;

int main() {
    Matrix<double> matrix = inputMatrix<double>("inputMatrix.txt");
    cout << "\nMatrix:\n";
    printMatrix(matrix);
    QRMatrix<double> QRDecomposition(matrix);

    auto res = findEigenvaluesAndEigenvectorsByQR(matrix, 0.001, 0.0001);
    printVector(res.eigenValues);
    return 0;
}
